#pragma once

#include <cstdint>
#include <any>
#include <string>
#include <istream>
#include <ostream>

namespace Tsubasa
{
    class Flow
    {
    public:
        template <typename T>
        static T Read(std::istream &stream)
        {
            T data;
            if (!(stream.read(reinterpret_cast<char *>(&data), sizeof(T))))
                throw std::runtime_error("Read operation failed.");
            return data;
        }

        template <typename T>
        static std::ostream &Write(std::ostream &stream, const T &data)
        {
            return stream.write(reinterpret_cast<const char *>(&data), sizeof(T));
        }

        // Specialized functions for strings
        static std::string ReadString(std::istream &stream);
        static std::ostream &WriteString(std::ostream &stream, const std::string &value);

        // Utility Functions for Raw Data
        static void *Read(std::istream &stream, void *data, const uint32_t size);
        static std::ostream &Write(std::ostream &stream, const void *data, const uint32_t size);
    };
}