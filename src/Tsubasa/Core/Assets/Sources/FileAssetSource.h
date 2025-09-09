#pragma once

#include <Tsubasa/Core/Assets/AssetSource.h>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace Tsubasa
{
    class FileAssetSource : public AssetSource
    {
    private:
        std::string basePath;

    public:
        explicit FileAssetSource(std::string base = "./") : basePath(std::move(base)) {}

        std::vector<uint8_t> ReadBinary(const std::string &path) override;

        std::string ReadText(const std::string &path) override;

        bool Exists(const std::string &path) const override;
    };
}
