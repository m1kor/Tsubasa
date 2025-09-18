#pragma once

#include <Tsubasa/Core/Graphics/PostprocessEffect.h>

namespace Tsubasa
{
    class BlurEffect : public PostprocessEffect
    {
    public:
        BlurEffect(float blurAmount = 2.0f);
        
        void SetBlurAmount(float amount);
        float GetBlurAmount() const { return blurAmount; }

    private:
        float blurAmount;
        static std::shared_ptr<Shader> CreateBlurShader();
    };
}