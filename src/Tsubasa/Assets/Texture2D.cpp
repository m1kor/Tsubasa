#include <Tsubasa/Assets/Texture2D.h>

namespace Tsubasa
{
    Texture2D::Texture2D(const std::string path, const std::vector<uint8_t> data, TextureFilter filter)
        : filter(filter), Filter(filter)
    {
        image = ::LoadImageFromMemory(".png", data.data(), static_cast<int>(data.size()));
        texture = ::LoadTextureFromImage(image);
        SetFilter(filter);
        ::UnloadImage(image);
    }

    Texture2D::~Texture2D()
    {
        ::UnloadTexture(texture);
    }

    void Texture2D::SetFilter(const TextureFilter &filter)
    {
        this->filter = filter;
        int raylibFilter;
        switch (filter)
        {
        case TextureFilter::Point:
            raylibFilter = TEXTURE_FILTER_POINT;
            break;
        case TextureFilter::Bilinear:
            raylibFilter = TEXTURE_FILTER_BILINEAR;
            break;
        case TextureFilter::Trilinear:
            raylibFilter = TEXTURE_FILTER_TRILINEAR;
            break;
        case TextureFilter::Anisotropic4x:
            raylibFilter = TEXTURE_FILTER_ANISOTROPIC_4X;
            break;
        case TextureFilter::Anisotropic8x:
            raylibFilter = TEXTURE_FILTER_ANISOTROPIC_8X;
            break;
        case TextureFilter::Anisotropic16x:
            raylibFilter = TEXTURE_FILTER_ANISOTROPIC_16X;
            break;
        default:
            raylibFilter = TEXTURE_FILTER_TRILINEAR;
            break;
        }
        ::SetTextureFilter(texture, raylibFilter);
    }
}
