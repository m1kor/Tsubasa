#include <Tsubasa/Components/Camera.h>
#include <Tsubasa/Core/Graphics/RenderTexture.h>
#include <Tsubasa/Core/Graphics/PostprocessEffect.h>
#include <algorithm>

namespace Tsubasa
{
    Camera::Camera(float fieldOfView, CameraProjection projection)
    {
        Projection = projection;
        FieldOfView = fieldOfView;
    }
    
    Camera::~Camera() = default;

    void Camera::SetRenderTarget(std::shared_ptr<RenderTexture> renderTarget)
    {
        this->renderTarget = renderTarget;
    }

    void Camera::AddPostprocessEffect(std::shared_ptr<PostprocessEffect> effect)
    {
        if (effect)
        {
            postprocessEffects.push_back(effect);
        }
    }

    void Camera::RemovePostprocessEffect(std::shared_ptr<PostprocessEffect> effect)
    {
        postprocessEffects.erase(
            std::remove(postprocessEffects.begin(), postprocessEffects.end(), effect),
            postprocessEffects.end()
        );
    }

    void Camera::ClearPostprocessEffects()
    {
        postprocessEffects.clear();
    }
}