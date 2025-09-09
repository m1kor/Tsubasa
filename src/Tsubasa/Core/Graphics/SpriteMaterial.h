#pragma once

#include <Tsubasa/Core/Graphics/Texture2D.h>
#include <raylib/raylib.h>
#include <memory>

namespace Tsubasa
{
    class SpriteMaterial
    {
    public:
        SpriteMaterial(std::shared_ptr<Texture2D> texture = nullptr, Color tint = WHITE);
        ~SpriteMaterial() = default;

        std::shared_ptr<Texture2D> GetTexture() const;
        void SetTexture(std::shared_ptr<Texture2D> texture);

        Color GetTint() const;
        void SetTint(Color tint);

    private:
        std::shared_ptr<Texture2D> texture;
        Color tint;
    };
}