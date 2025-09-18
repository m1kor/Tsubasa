#include "PostprocessEffect.h"
#include <raylib/raylib.h>

namespace Tsubasa
{
    PostprocessEffect::PostprocessEffect(std::shared_ptr<Shader> shader)
        : shader(shader)
    {
    }

    void PostprocessEffect::Apply(::Texture2D inputTexture)
    {
        if (!shader || !shader->IsValid()) return;

        BeginShaderMode(shader->GetRaylibShader());
        DrawTextureRec(inputTexture, Rectangle{0, 0, (float)inputTexture.width, -(float)inputTexture.height}, ::Vector2{0, 0}, WHITE);
        EndShaderMode();
    }
}