#pragma once

#include <Tsubasa/System.h>
#include <Tsubasa/Components/Camera.h>
#include <string>
#include <vector>
#include <memory>
#include <raylib/raylib.h>

namespace Tsubasa
{
    struct LaunchOptions
    {
        int ScreenWidth;
        int ScreenHeight;
        std::string WindowTitle;
        bool Fullscreen;
        bool VSync;
    };

    struct SpriteInstanceData;

    class MeshRenderer;
    class SpriteRenderer;
    class SpriteMaterial;

    class RaylibRenderSystem : public System
    {
    public:
        RaylibRenderSystem();
        RaylibRenderSystem(LaunchOptions options);
        ~RaylibRenderSystem();

        void OnInit() override;
        bool OnUpdate(float timeDelta) override;
        void OnExit() override;

        LaunchOptions Options;
    
    private:
        void beginMode3D(std::shared_ptr<Camera> camera);
        void beginMode2D();
        void endMode2D();
        void renderModel(std::shared_ptr<MeshRenderer> meshRenderer);
        void renderSprite(std::shared_ptr<SpriteRenderer> spriteRenderer);
        void renderSpriteBatch(unsigned int textureId, std::shared_ptr<SpriteMaterial> material, const std::vector<struct SpriteInstanceData> &instances);
    };
}
