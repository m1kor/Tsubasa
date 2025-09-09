#include <Tsubasa/Core/Assets/Sources/FileAssetSource.h>

namespace Tsubasa
{
    std::vector<uint8_t> FileAssetSource::ReadBinary(const std::string &path)
    {
        std::ifstream file(basePath + path, std::ios::binary);
        if (!file)
            throw std::runtime_error("Cannot open file: " + path);

        return std::vector<uint8_t>(std::istreambuf_iterator<char>(file),
                                    std::istreambuf_iterator<char>());
    }

    std::string FileAssetSource::ReadText(const std::string &path)
    {
        std::ifstream file(basePath + path);
        if (!file)
            throw std::runtime_error("Cannot open file: " + path);

        return std::string(std::istreambuf_iterator<char>(file),
                            std::istreambuf_iterator<char>());
    }

    bool FileAssetSource::Exists(const std::string &path) const
    {
        return std::filesystem::exists(basePath + path);
    }
}
