#pragma once

#include <raylib/raylib.h>

namespace Tsubasa
{
    class RenderTexture
    {
    public:
        RenderTexture(int width, int height);
        ~RenderTexture();

        RenderTexture(const RenderTexture&) = delete;
        RenderTexture& operator=(const RenderTexture&) = delete;

        RenderTexture(RenderTexture&& other) noexcept;
        RenderTexture& operator=(RenderTexture&& other) noexcept;

        void Begin();
        void End();
        
        ::Texture2D GetTexture() const { return renderTexture.texture; }
        int GetWidth() const { return width; }
        int GetHeight() const { return height; }
        bool IsValid() const { return renderTexture.id > 0; }

    private:
        RenderTexture2D renderTexture;
        int width;
        int height;
    };
}