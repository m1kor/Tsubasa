#include "VignetteEffect.h"

namespace Tsubasa
{
    VignetteEffect::VignetteEffect(float intensity, float radius)
        : PostprocessEffect(CreateVignetteShader()), intensity(intensity), radius(radius)
    {
        if (shader)
        {
            shader->SetUniform("vignetteIntensity", intensity);
            shader->SetUniform("vignetteRadius", radius);
        }
    }

    void VignetteEffect::SetIntensity(float intensity)
    {
        this->intensity = intensity;
        if (shader)
        {
            shader->SetUniform("vignetteIntensity", intensity);
        }
    }

    void VignetteEffect::SetRadius(float radius)
    {
        this->radius = radius;
        if (shader)
        {
            shader->SetUniform("vignetteRadius", radius);
        }
    }

    std::shared_ptr<Shader> VignetteEffect::CreateVignetteShader()
    {
        const char* vertexShader = R"(
            #version 330 core
            in vec3 vertexPosition;
            in vec2 vertexTexCoord;
            in vec4 vertexColor;
            
            out vec2 fragTexCoord;
            out vec4 fragColor;
            
            uniform mat4 mvp;
            
            void main()
            {
                fragTexCoord = vertexTexCoord;
                fragColor = vertexColor;
                gl_Position = mvp * vec4(vertexPosition, 1.0);
            }
        )";

        const char* fragmentShader = R"(
            #version 330 core
            in vec2 fragTexCoord;
            in vec4 fragColor;
            
            uniform sampler2D texture0;
            uniform float vignetteIntensity;
            uniform float vignetteRadius;
            
            out vec4 finalColor;
            
            void main()
            {
                vec4 color = texture(texture0, fragTexCoord);
                
                // Calculate distance from center
                vec2 center = vec2(0.5, 0.5);
                float distance = length(fragTexCoord - center);
                
                // Apply vignette
                float vignette = smoothstep(vignetteRadius, vignetteRadius - 0.3, distance);
                color.rgb *= mix(1.0 - vignetteIntensity, 1.0, vignette);
                
                finalColor = color;
            }
        )";

        return std::make_shared<Shader>(vertexShader, fragmentShader);
    }
}