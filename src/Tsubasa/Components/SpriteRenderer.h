#include <Tsubasa/Component.h>
#include <Tsubasa/Core/Graphics/Texture2D.h>
#include <Tsubasa/Math/Vector2.h>
#include <memory>

namespace Tsubasa
{
    class SpriteRenderer : public Component
    {
    public:
        SpriteRenderer(std::shared_ptr<Texture2D> texture = nullptr);
        ~SpriteRenderer() = default;

        std::shared_ptr<Texture2D> Texture;
        Vector2 Pivot = Vector2(0.5f, 0.5f);
    };
}
