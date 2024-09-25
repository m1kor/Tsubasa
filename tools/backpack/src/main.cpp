#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <Tsubasa/Flow.h>
#include <lz4/lz4.h>

using namespace Tsubasa;

struct Asset
{
    enum AssetType
    {
        ARBITRARY,
        TEXTURE,
        SOUND
    };

    std::string Key;
    std::filesystem::path Path;
    std::list<std::string> Tags;
    AssetType Type;
    bool Compressed;
    uint32_t Size;
    std::streampos Offset;

    friend std::ostream &operator<<(std::ostream &os, Asset &asset)
    {
        Flow::WriteString(os, asset.Key);
        Flow::Write<uint16_t>(os, asset.Tags.size());
        for (auto tag : asset.Tags)
        {
            Flow::WriteString(os, tag);
        }
        Flow::Write<uint8_t>(os, asset.Type);
        Flow::Write<uint8_t>(os, asset.Compressed);
        Flow::Write<uint32_t>(os, asset.Size);
        asset.Offset = os.tellp();
        Flow::Write<uint64_t>(os, 0); // Temporary value
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Asset &asset)
    {
        asset.Key = Flow::ReadString(is);
        int tagsSize = Flow::Read<uint16_t>(is);
        for (int i = 0; i < tagsSize; i++)
        {
            std::string tag = Flow::ReadString(is);
            asset.Tags.push_back(tag);
        }
        asset.Type = (Asset::AssetType)Flow::Read<uint8_t>(is);
        asset.Compressed = Flow::Read<uint8_t>(is);
        asset.Size = Flow::Read<uint32_t>(is);
        asset.Offset = Flow::Read<uint64_t>(is);
        return is;
    }
};

class Table
{
public:
    std::list<Asset> Assets;

    static const std::string Header;

    void AddFile(std::string key, std::filesystem::path path, Asset::AssetType type = Asset::AssetType::ARBITRARY, bool compressed = false, std::list<std::string> tags = std::list<std::string>())
    {
        Asset asset;
        asset.Key = key;
        asset.Path = path;
        asset.Type = type;
        asset.Compressed = true;
        asset.Size = std::filesystem::file_size(path);
        Assets.push_back(asset);
    }

    void AddRecursive(std::filesystem::path rootPath, Asset::AssetType type = Asset::AssetType::ARBITRARY, bool compressed = false)
    {
        for (auto entry : std::filesystem::recursive_directory_iterator(rootPath))
        {
            if (std::filesystem::is_regular_file(entry.path()))
            {
                AddFile(std::filesystem::relative(entry.path(), rootPath).string(), entry.path(), type, compressed);
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &os, Table &table)
    {
        Flow::Write(os, table.Header.data(), Table::Header.size());
        Flow::Write<uint32_t>(os, table.Assets.size());
        for (auto &asset : table.Assets)
        {
            os << asset;
        }
        for (auto &asset : table.Assets)
        {
            std::streampos end = os.tellp();
            os.seekp(asset.Offset);
            Flow::Write<uint64_t>(os, end);
            os.seekp(0, std::ios::end);
            std::ifstream in(asset.Path, std::ios::binary);
            if (asset.Compressed)
            {
                in.seekg(0, std::ios::end);
                size_t size = in.tellg();
                in.seekg(0, std::ios::beg);
                std::vector<char> input(size);
                if (!in.read(input.data(), size))
                {
                    std::cerr << "Failed to read file\n";
                    return os;
                }
                int maxCompressedSize = LZ4_compressBound(size);
                std::vector<char> compressed(maxCompressedSize);
                int compressedSize = LZ4_compress_default(input.data(), compressed.data(), size, maxCompressedSize);
                if (compressedSize <= 0)
                {
                    std::cerr << "Compression failed\n";
                    return os;
                }
                Flow::Write(os, compressed.data(), compressedSize);
            }
            else
            {
                char c;
                while (!in.eof())
                {
                    in.get(c);
                    os.write(&c, sizeof(c));
                }
            }
            in.close();
        }
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Table &table)
    {
        is.ignore(Table::Header.size());
        uint32_t assetsSize = Flow::Read<uint32_t>(is);
        table.Assets.clear();
        for (uint32_t i = 0; i < assetsSize; i++)
        {
            Asset asset;
            is >> asset;
            table.Assets.push_back(asset);
        }
        return is;
    }
};

const std::string Table::Header = "BKPK";

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << std::endl;
        return 1;
    }
    Table table;
    if (std::filesystem::exists(std::string("bundle_cpp.bpk")))
    {
        std::filesystem::remove(std::string("bundle_cpp.bpk"));
    }
    table.AddRecursive(argv[1]);
    std::ofstream out("bundle_cpp.bpk", std::ios::binary);
    out << table;
    out.close();
    std::ifstream in("bundle_cpp.bpk", std::ios::binary);
    in >> table;
    for (auto a : table.Assets)
    {
        std::cout << a.Offset << std::endl;
    }
    in.close();
    return 0;
}
