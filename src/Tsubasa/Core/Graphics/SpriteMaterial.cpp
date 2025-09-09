#include <Tsubasa/Core/Graphics/SpriteMaterial.h>

namespace Tsubasa
{
    SpriteMaterial::SpriteMaterial(std::shared_ptr<Texture2D> texture, Vector4 tint)
        : texture(texture), Tint(tint)
    {
    }

    std::shared_ptr<Texture2D> SpriteMaterial::GetTexture() const
    {
        return texture;
    }

    void SpriteMaterial::SetTexture(std::shared_ptr<Texture2D> texture)
    {
        this->texture = texture;
    }
}