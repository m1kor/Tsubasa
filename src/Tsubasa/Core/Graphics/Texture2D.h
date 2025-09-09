#pragma once

#include <raylib/raylib.h>
#include <cstdint>
#include <string>
#include <vector>

namespace Tsubasa
{
    class RaylibRenderSystem;

    enum TextureFilter
    {
        Point,
        Bilinear,
        Trilinear,
        Anisotropic4x,
        Anisotropic8x,
        Anisotropic16x
    };
    
    class Texture2D
    {
        friend class RaylibRenderSystem;
        friend class Shader;
        
    public:
        Texture2D(const std::string path, const std::vector<uint8_t> data, TextureFilter filter = TextureFilter::Trilinear);
        ~Texture2D();

        const TextureFilter& Filter;
        void SetFilter(const TextureFilter &filter);
    private:
        ::Image image;
        ::Texture2D texture;
        TextureFilter filter;
    };
}
