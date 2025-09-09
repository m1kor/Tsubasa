#include <Tsubasa/Components/SpriteRenderer.h>

namespace Tsubasa
{
    SpriteRenderer::SpriteRenderer(std::shared_ptr<Texture2D> texture)
    {
        Texture = texture;
    }
}
