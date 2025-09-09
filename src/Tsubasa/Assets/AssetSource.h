#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace Tsubasa
{
    class AssetSource
    {
    public:
        virtual ~AssetSource() = default;
        virtual std::vector<uint8_t> ReadBinary(const std::string& identifier) = 0;
        virtual std::string ReadText(const std::string& identifier) = 0;
        virtual bool Exists(const std::string& identifier) const = 0;
    };
}
