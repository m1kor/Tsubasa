#include <Tsubasa/Flow.h>
#include <algorithm>
#include <iterator>

namespace Tsubasa
{
    void *Flow::Read(std::istream &stream, void *data, const uint32_t size)
    {
        stream.read((char *)data, size);
        return data;
    }

    std::string Flow::ReadString(std::istream &stream)
    {
        uint16_t size = Read<uint16_t>(stream);
        std::string value;
        std::copy_n(std::istream_iterator<char>(stream), size, std::insert_iterator<std::string>(value, value.begin()));
        return value;
    }

    std::ostream &Flow::Write(std::ostream &stream, const void *data, const uint32_t size)
    {
        return stream.write((char *)data, size);
    }

    std::ostream &Flow::WriteString(std::ostream &stream, const std::string &value)
    {
        Write<uint16_t>(stream, value.size());
        return stream.write(value.data(), value.size());
    }
}