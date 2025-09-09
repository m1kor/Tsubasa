#include <Tsubasa/Core/Graphics/SpriteMaterial.h>

namespace Tsubasa
{
    SpriteMaterial::SpriteMaterial(std::shared_ptr<Texture2D> texture, Vector4 tint, std::shared_ptr<Shader> shader)
        : texture(texture), Tint(tint), shader(shader)
    {
        // Use default shader if none provided
        if (!this->shader)
        {
            this->shader = Shader::CreateDefault();
        }
    }

    std::shared_ptr<Texture2D> SpriteMaterial::GetTexture() const
    {
        return texture;
    }

    void SpriteMaterial::SetTexture(std::shared_ptr<Texture2D> texture)
    {
        this->texture = texture;
    }

    std::shared_ptr<Shader> SpriteMaterial::GetShader() const
    {
        return shader;
    }

    void SpriteMaterial::SetShader(std::shared_ptr<Shader> shader)
    {
        this->shader = shader ? shader : Shader::CreateDefault();
    }

    void SpriteMaterial::SetFloat(const std::string& name, float value)
    {
        if (shader)
        {
            shader->SetUniform(name, value);
        }
    }

    void SpriteMaterial::SetInt(const std::string& name, int value)
    {
        if (shader)
        {
            shader->SetUniform(name, value);
        }
    }

    void SpriteMaterial::SetVector2(const std::string& name, const Vector2& value)
    {
        if (shader)
        {
            shader->SetUniform(name, value);
        }
    }

    void SpriteMaterial::SetVector3(const std::string& name, const Vector3& value)
    {
        if (shader)
        {
            shader->SetUniform(name, value);
        }
    }

    void SpriteMaterial::SetVector4(const std::string& name, const Vector4& value)
    {
        if (shader)
        {
            shader->SetUniform(name, value);
        }
    }

    void SpriteMaterial::SetMatrix4x4(const std::string& name, const Matrix4x4& value)
    {
        if (shader)
        {
            shader->SetUniform(name, value);
        }
    }

    void SpriteMaterial::SetTexture(const std::string& name, std::shared_ptr<Texture2D> texture, int slot)
    {
        if (shader)
        {
            shader->SetUniform(name, texture, slot);
        }
    }
}