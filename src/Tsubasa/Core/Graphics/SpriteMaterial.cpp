#include <Tsubasa/Core/Graphics/SpriteMaterial.h>

namespace Tsubasa
{
    SpriteMaterial::SpriteMaterial(std::shared_ptr<Texture2D> texture, Color tint)
        : texture(texture), tint(tint)
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

    Color SpriteMaterial::GetTint() const
    {
        return tint;
    }

    void SpriteMaterial::SetTint(Color tint)
    {
        this->tint = tint;
    }
}