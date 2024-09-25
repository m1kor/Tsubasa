#include <Tsubasa/Components/Camera.h>

namespace Tsubasa
{
    Camera::Camera(float fieldOfView, CameraProjection projection)
    {
        Projection = projection;
        FieldOfView = fieldOfView;
    }
    
    Camera::~Camera() {}
}