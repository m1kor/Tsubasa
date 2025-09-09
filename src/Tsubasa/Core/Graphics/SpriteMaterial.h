#pragma once

#include <Tsubasa/Core/Graphics/Texture2D.h>
#include <Tsubasa/Core/Graphics/Shader.h>
#include <Tsubasa/Math/Vector2.h>
#include <Tsubasa/Math/Vector3.h>
#include <Tsubasa/Math/Vector4.h>
#include <Tsubasa/Math/Matrix4x4.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>

namespace Tsubasa
{
    class SpriteMaterial
    {
        friend class RaylibRenderSystem;

    public:
        // Uniform value types
        using UniformValue = std::variant<float, int, Vector2, Vector3, Vector4, Matrix4x4, std::pair<std::shared_ptr<Texture2D>, int>>;

        SpriteMaterial(std::shared_ptr<Texture2D> texture = nullptr, Vector4 tint = Vector4(1.0f, 1.0f, 1.0f, 1.0f), std::shared_ptr<Shader> shader = nullptr);
        ~SpriteMaterial() = default;

        std::shared_ptr<Texture2D> GetTexture() const;
        void SetTexture(std::shared_ptr<Texture2D> texture);

        std::shared_ptr<Shader> GetShader() const;
        void SetShader(std::shared_ptr<Shader> shader);

        // Shader uniform setters (stores values instead of setting immediately)
        void SetFloat(const std::string &name, float value);
        void SetInt(const std::string &name, int value);
        void SetVector2(const std::string &name, const Vector2 &value);
        void SetVector3(const std::string &name, const Vector3 &value);
        void SetVector4(const std::string &name, const Vector4 &value);
        void SetMatrix4x4(const std::string &name, const Matrix4x4 &value);
        void SetTexture(const std::string &name, std::shared_ptr<Texture2D> texture, int slot = 0);

        Vector4 Tint;

    private:
        std::shared_ptr<Texture2D> texture;
        std::shared_ptr<Shader> shader;
        std::unordered_map<std::string, UniformValue> uniforms;

        void applyUniforms() const;
    };
}