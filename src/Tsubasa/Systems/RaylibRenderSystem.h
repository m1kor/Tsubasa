#pragma once

#include <Tsubasa/System.h>
#include <Tsubasa/Components/Camera.h>
#include <string>

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

    class MeshRenderer;

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
        void renderModel(std::shared_ptr<MeshRenderer> meshRenderer);
    };
}