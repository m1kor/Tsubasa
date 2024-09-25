#pragma once

#include <Tsubasa/Component.h>

namespace Tsubasa
{
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
    };
}