#include <Tsubasa/Core/Graphics/Shader.h>
#include <Tsubasa/Core/Graphics/Texture2D.h>
#include <raylib/raylib.h>
#include <raylib/rlgl.h>
#include <raylib/raymath.h>
#include <iostream>
#include <typeindex>

namespace Tsubasa
{
    Shader::Shader(const std::string &vertexShaderCode, const std::string &fragmentShaderCode)
    {
        shader = LoadShaderFromMemory(vertexShaderCode.c_str(), fragmentShaderCode.c_str());
        if (!IsValid())
        {
            std::cerr << "Failed to create shader from memory" << std::endl;
        }
    }

    Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath, bool isPath)
    {
        shader = LoadShader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
        if (!IsValid())
        {
            std::cerr << "Failed to load shader from files: " << vertexShaderPath << ", " << fragmentShaderPath << std::endl;
        }
    }

    Shader::~Shader()
    {
        if (IsValid())
        {
            UnloadShader(shader);
        }
    }

    Shader::Shader(Shader &&other) noexcept
        : shader(other.shader), uniformLocations(std::move(other.uniformLocations)), uniformTypes(std::move(other.uniformTypes))
    {
        other.shader = {0};
    }

    Shader &Shader::operator=(Shader &&other) noexcept
    {
        if (this != &other)
        {
            if (IsValid())
            {
                UnloadShader(shader);
            }
            shader = other.shader;
            uniformLocations = std::move(other.uniformLocations);
            uniformTypes = std::move(other.uniformTypes);
            other.shader = {0};
        }
        return *this;
    }

    void Shader::SetUniform(const std::string &name, float value)
    {
        if (!IsValid())
            return;
        int location = getUniformLocation(name);
        if (location >= 0)
        {
            uniformTypes.insert_or_assign(name, std::type_index(typeid(float)));
            SetShaderValue(shader, location, &value, SHADER_UNIFORM_FLOAT);
        }
    }

    void Shader::SetUniform(const std::string &name, int value)
    {
        if (!IsValid())
            return;
        int location = getUniformLocation(name);
        if (location >= 0)
        {
            uniformTypes.insert_or_assign(name, std::type_index(typeid(int)));
            SetShaderValue(shader, location, &value, SHADER_UNIFORM_INT);
        }
    }

    void Shader::SetUniform(const std::string &name, const Vector2 &value)
    {
        if (!IsValid())
            return;
        int location = getUniformLocation(name);
        if (location >= 0)
        {
            uniformTypes.insert_or_assign(name, std::type_index(typeid(Vector2)));
            float values[2] = {value.x, value.y};
            SetShaderValue(shader, location, values, SHADER_UNIFORM_VEC2);
        }
    }

    void Shader::SetUniform(const std::string &name, const Vector3 &value)
    {
        if (!IsValid())
            return;
        int location = getUniformLocation(name);
        if (location >= 0)
        {
            uniformTypes.insert_or_assign(name, std::type_index(typeid(Vector3)));
            float values[3] = {value.x, value.y, value.z};
            SetShaderValue(shader, location, values, SHADER_UNIFORM_VEC3);
        }
    }

    void Shader::SetUniform(const std::string &name, const Vector4 &value)
    {
        if (!IsValid())
            return;
        int location = getUniformLocation(name);
        if (location >= 0)
        {
            uniformTypes.insert_or_assign(name, std::type_index(typeid(Vector4)));
            float values[4] = {value.x, value.y, value.z, value.w};
            SetShaderValue(shader, location, values, SHADER_UNIFORM_VEC4);
        }
    }

    void Shader::SetUniform(const std::string &name, const Matrix4x4 &value)
    {
        if (!IsValid())
            return;
        int location = getUniformLocation(name);
        if (location >= 0)
        {
            uniformTypes.insert_or_assign(name, std::type_index(typeid(Matrix4x4)));
            SetShaderValueMatrix(shader, location, *reinterpret_cast<const ::Matrix *>(&value));
        }
    }

    void Shader::SetUniform(const std::string &name, std::shared_ptr<Texture2D> texture, int slot)
    {
        if (!IsValid() || !texture)
            return;
        int location = getUniformLocation(name);
        if (location >= 0)
        {
            uniformTypes.insert_or_assign(name, std::type_index(typeid(std::shared_ptr<Texture2D>)));
            SetShaderValueTexture(shader, location, texture->texture);
        }
    }

    void Shader::ResetUniforms()
    {
        if (!IsValid())
            return;

        // Reset all tracked uniforms to their default values
        for (const auto &[name, type] : uniformTypes)
        {
            resetUniformToDefault(name, type);
        }

        // Clear tracking since uniforms are now reset
        uniformTypes.clear();
    }

    // Static factory methods for common 2D shaders
    std::shared_ptr<Shader> Shader::CreateDefault()
    {
        const char *vertexShader = R"(
#version 330
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;

uniform mat4 mvp;

out vec2 fragTexCoord;
out vec4 fragColor;

void main()
{
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
)";

        const char *fragmentShader = R"(
#version 330
in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;

out vec4 finalColor;

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord);
    finalColor = texelColor * fragColor;
}
)";

        return std::make_shared<Shader>(vertexShader, fragmentShader);
    }

    std::shared_ptr<Shader> Shader::CreateTinted()
    {
        const char *vertexShader = R"(
#version 330
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;

uniform mat4 mvp;

out vec2 fragTexCoord;
out vec4 fragColor;

void main()
{
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
)";

        const char *fragmentShader = R"(
#version 330
in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 tintColor;

out vec4 finalColor;

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord);
    finalColor = texelColor * fragColor * tintColor;
}
)";

        return std::make_shared<Shader>(vertexShader, fragmentShader);
    }

    std::shared_ptr<Shader> Shader::CreateDissolve()
    {
        const char *vertexShader = R"(
#version 330
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;

uniform mat4 mvp;

out vec2 fragTexCoord;
out vec4 fragColor;

void main()
{
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
)";

        const char *fragmentShader = R"(
#version 330
in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform sampler2D noiseTexture;
uniform float dissolveAmount;
uniform vec4 dissolveColor;
uniform float edgeWidth;

out vec4 finalColor;

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord);
    float noise = texture(noiseTexture, fragTexCoord).r;
    
    if (noise < dissolveAmount)
    {
        discard;
    }
    
    float edge = smoothstep(dissolveAmount, dissolveAmount + edgeWidth, noise);
    vec4 edgeColor = mix(dissolveColor, texelColor, edge);
    
    finalColor = edgeColor * fragColor;
}
)";

        return std::make_shared<Shader>(vertexShader, fragmentShader);
    }

    std::shared_ptr<Shader> Shader::CreateOutline()
    {
        const char *vertexShader = R"(
#version 330
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;

uniform mat4 mvp;

out vec2 fragTexCoord;
out vec4 fragColor;

void main()
{
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
)";

        const char *fragmentShader = R"(
#version 330
in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 outlineColor;
uniform float outlineWidth;
uniform vec2 textureSize;

out vec4 finalColor;

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord);
    
    if (texelColor.a > 0.1)
    {
        finalColor = texelColor * fragColor;
        return;
    }
    
    vec2 pixelSize = 1.0 / textureSize;
    float outline = 0.0;
    
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (x == 0 && y == 0) continue;
            
            vec2 offset = vec2(float(x), float(y)) * pixelSize * outlineWidth;
            float alpha = texture(texture0, fragTexCoord + offset).a;
            outline = max(outline, alpha);
        }
    }
    
    finalColor = mix(vec4(0.0), outlineColor, outline);
}
)";

        return std::make_shared<Shader>(vertexShader, fragmentShader);
    }

    int Shader::getUniformLocation(const std::string &name)
    {
        auto it = uniformLocations.find(name);
        if (it != uniformLocations.end())
        {
            return it->second;
        }

        int location = GetShaderLocation(shader, name.c_str());
        uniformLocations[name] = location;
        return location;
    }

    void Shader::resetUniformToDefault(const std::string &name, std::type_index type)
    {
        int location = getUniformLocation(name);
        if (location < 0)
            return;

        if (type == std::type_index(typeid(float)))
        {
            float defaultValue = 0.0f;
            SetShaderValue(shader, location, &defaultValue, SHADER_UNIFORM_FLOAT);
        }
        else if (type == std::type_index(typeid(int)))
        {
            int defaultValue = 0;
            SetShaderValue(shader, location, &defaultValue, SHADER_UNIFORM_INT);
        }
        else if (type == std::type_index(typeid(Vector2)))
        {
            float defaultValue[2] = {0.0f, 0.0f};
            SetShaderValue(shader, location, defaultValue, SHADER_UNIFORM_VEC2);
        }
        else if (type == std::type_index(typeid(Vector3)))
        {
            float defaultValue[3] = {0.0f, 0.0f, 0.0f};
            SetShaderValue(shader, location, defaultValue, SHADER_UNIFORM_VEC3);
        }
        else if (type == std::type_index(typeid(Vector4)))
        {
            float defaultValue[4] = {1.0f, 1.0f, 1.0f, 1.0f}; // Default to white for colors
            SetShaderValue(shader, location, defaultValue, SHADER_UNIFORM_VEC4);
        }
        else if (type == std::type_index(typeid(Matrix4x4)))
        {
            Matrix identity = MatrixIdentity();
            SetShaderValueMatrix(shader, location, identity);
        }
        // Note: Texture2D uniforms don't need resetting as textures are managed externally
    }
}
