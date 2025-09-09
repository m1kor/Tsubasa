#pragma once

#include <Tsubasa/Core/Graphics/Texture2D.h>
#include <Tsubasa/Math/Vector4.h>
#include <memory>

namespace Tsubasa
{
    class SpriteMaterial
    {
    public:
        SpriteMaterial(std::shared_ptr<Texture2D> texture = nullptr, Vector4 tint = Vector4(1.0f, 1.0f, 1.0f, 1.0f));
        ~SpriteMaterial() = default;

        std::shared_ptr<Texture2D> GetTexture() const;
        void SetTexture(std::shared_ptr<Texture2D> texture);

        Vector4 Tint;

    private:
        std::shared_ptr<Texture2D> texture;
    };
}