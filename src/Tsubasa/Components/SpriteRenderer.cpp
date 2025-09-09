#include <Tsubasa/Components/SpriteRenderer.h>

namespace Tsubasa
{
    SpriteRenderer::SpriteRenderer(std::shared_ptr<SpriteMaterial> sprite)
    {
        this->Sprite = sprite;
    }
}
