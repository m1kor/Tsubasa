#include "RenderTexture.h"
#include <raylib/rlgl.h>

namespace Tsubasa
{
    RenderTexture::RenderTexture(int width, int height)
        : width(width), height(height)
    {
        renderTexture = LoadRenderTexture(width, height);
    }

    RenderTexture::~RenderTexture()
    {
        if (IsValid())
        {
            UnloadRenderTexture(renderTexture);
        }
    }

    RenderTexture::RenderTexture(RenderTexture&& other) noexcept
        : renderTexture(other.renderTexture), width(other.width), height(other.height)
    {
        other.renderTexture.id = 0;
        other.width = 0;
        other.height = 0;
    }

    RenderTexture& RenderTexture::operator=(RenderTexture&& other) noexcept
    {
        if (this != &other)
        {
            if (IsValid())
            {
                UnloadRenderTexture(renderTexture);
            }
            
            renderTexture = other.renderTexture;
            width = other.width;
            height = other.height;
            
            other.renderTexture.id = 0;
            other.width = 0;
            other.height = 0;
        }
        return *this;
    }

    void RenderTexture::Begin()
    {
        BeginTextureMode(renderTexture);
        rlViewport(0, 0, width, height);
    }

    void RenderTexture::End()
    {
        EndTextureMode();
    }
}