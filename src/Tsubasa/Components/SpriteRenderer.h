#include <Tsubasa/Component.h>
#include <Tsubasa/Math/Vector2.h>
#include <Tsubasa/Core/Graphics/SpriteMaterial.h>
#include <memory>

namespace Tsubasa
{
    class SpriteRenderer : public Component
    {
    public:
        SpriteRenderer(std::shared_ptr<SpriteMaterial> sprite = nullptr);
        ~SpriteRenderer() = default;

        std::shared_ptr<SpriteMaterial> Sprite;
        Vector2 Pivot = Vector2(0.5f, 0.5f);
    };
}
