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

    void SpriteMaterial::SetFloat(const std::string &name, float value)
    {
        uniforms[name] = value;
    }

    void SpriteMaterial::SetInt(const std::string &name, int value)
    {
        uniforms[name] = value;
    }

    void SpriteMaterial::SetVector2(const std::string &name, const Vector2 &value)
    {
        uniforms[name] = value;
    }

    void SpriteMaterial::SetVector3(const std::string &name, const Vector3 &value)
    {
        uniforms[name] = value;
    }

    void SpriteMaterial::SetVector4(const std::string &name, const Vector4 &value)
    {
        uniforms[name] = value;
    }

    void SpriteMaterial::SetMatrix4x4(const std::string &name, const Matrix4x4 &value)
    {
        uniforms[name] = value;
    }

    void SpriteMaterial::SetTexture(const std::string &name, std::shared_ptr<Texture2D> texture, int slot)
    {
        uniforms[name] = std::make_pair(texture, slot);
    }

    void SpriteMaterial::applyUniforms() const
    {
        if (!shader)
            return;

        for (const auto &[name, value] : uniforms)
        {
            std::visit([&](const auto &v)
                       {
                using T = std::decay_t<decltype(v)>;
                if constexpr (std::is_same_v<T, float>)
                {
                    shader->SetUniform(name, v);
                }
                else if constexpr (std::is_same_v<T, int>)
                {
                    shader->SetUniform(name, v);
                }
                else if constexpr (std::is_same_v<T, Vector2>)
                {
                    shader->SetUniform(name, v);
                }
                else if constexpr (std::is_same_v<T, Vector3>)
                {
                    shader->SetUniform(name, v);
                }
                else if constexpr (std::is_same_v<T, Vector4>)
                {
                    shader->SetUniform(name, v);
                }
                else if constexpr (std::is_same_v<T, Matrix4x4>)
                {
                    shader->SetUniform(name, v);
                }
                else if constexpr (std::is_same_v<T, std::pair<std::shared_ptr<Texture2D>, int>>)
                {
                    shader->SetUniform(name, v.first, v.second);
                } }, value);
        }
    }
}