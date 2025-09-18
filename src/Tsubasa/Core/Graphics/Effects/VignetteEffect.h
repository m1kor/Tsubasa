#pragma once

#include <Tsubasa/Core/Graphics/PostprocessEffect.h>

namespace Tsubasa
{
    class VignetteEffect : public PostprocessEffect
    {
    public:
        VignetteEffect(float intensity = 0.5f, float radius = 0.8f);
        
        void SetIntensity(float intensity);
        void SetRadius(float radius);
        
        float GetIntensity() const { return intensity; }
        float GetRadius() const { return radius; }

    private:
        float intensity;
        float radius;
        static std::shared_ptr<Shader> CreateVignetteShader();
    };
}