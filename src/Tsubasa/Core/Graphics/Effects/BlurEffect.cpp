#include "BlurEffect.h"

namespace Tsubasa
{
    BlurEffect::BlurEffect(float blurAmount)
        : PostprocessEffect(CreateBlurShader()), blurAmount(blurAmount)
    {
        if (shader)
        {
            shader->SetUniform("blurAmount", blurAmount);
        }
    }

    void BlurEffect::SetBlurAmount(float amount)
    {
        blurAmount = amount;
        if (shader)
        {
            shader->SetUniform("blurAmount", blurAmount);
        }
    }

    std::shared_ptr<Shader> BlurEffect::CreateBlurShader()
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
            uniform float blurAmount;
            
            out vec4 finalColor;
            
            void main()
            {
                vec2 texelSize = 1.0 / textureSize(texture0, 0);
                vec4 color = vec4(0.0);
                
                // Simple box blur
                for (int x = -2; x <= 2; x++)
                {
                    for (int y = -2; y <= 2; y++)
                    {
                        vec2 offset = vec2(float(x), float(y)) * texelSize * blurAmount;
                        color += texture(texture0, fragTexCoord + offset);
                    }
                }
                
                finalColor = color / 25.0; // Average of 5x5 samples
            }
        )";

        return std::make_shared<Shader>(vertexShader, fragmentShader);
    }
}