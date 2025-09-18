#pragma once

#include <Tsubasa/Core/Graphics/Shader.h>
#include <memory>

namespace Tsubasa
{
    class PostprocessEffect
    {
    public:
        PostprocessEffect(std::shared_ptr<Shader> shader);
        virtual ~PostprocessEffect() = default;

        virtual void Apply(::Texture2D inputTexture);
        
        std::shared_ptr<Shader> GetShader() const { return shader; }

    protected:
        std::shared_ptr<Shader> shader;
    };
}