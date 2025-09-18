#pragma once

#include <Tsubasa/Component.h>
#include <memory>
#include <vector>

namespace Tsubasa
{
    class RenderTexture;
    class PostprocessEffect;

    enum class CameraProjection
    {
        Perspective,
        Orthographic
    };

    class Camera : public Component
    {
    public:
        Camera(float fieldOfView = 45.0f, CameraProjection projection = CameraProjection::Perspective);
        ~Camera();

        float FieldOfView;
        CameraProjection Projection;
        
        // Render target
        void SetRenderTarget(std::shared_ptr<RenderTexture> renderTarget);
        std::shared_ptr<RenderTexture> GetRenderTarget() const { return renderTarget; }
        
        // Postprocessing
        void AddPostprocessEffect(std::shared_ptr<PostprocessEffect> effect);
        void RemovePostprocessEffect(std::shared_ptr<PostprocessEffect> effect);
        void ClearPostprocessEffects();
        const std::vector<std::shared_ptr<PostprocessEffect>>& GetPostprocessEffects() const { return postprocessEffects; }

    private:
        std::shared_ptr<RenderTexture> renderTarget;
        std::vector<std::shared_ptr<PostprocessEffect>> postprocessEffects;
    };
}