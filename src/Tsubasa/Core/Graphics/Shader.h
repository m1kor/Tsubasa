#pragma once

#include <Tsubasa/Math/Vector2.h>
#include <Tsubasa/Math/Vector3.h>
#include <Tsubasa/Math/Vector4.h>
#include <Tsubasa/Math/Matrix4x4.h>
#include <raylib/raylib.h>
#include <string>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <optional>

namespace Tsubasa
{
    class Texture2D;

    class Shader
    {
        friend class RaylibRenderSystem;
    public:
        Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, bool isPath);
        ~Shader();

        // Disable copy constructor and assignment operator
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        // Enable move constructor and assignment operator
        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        // Uniform setters
        void SetUniform(const std::string& name, float value);
        void SetUniform(const std::string& name, int value);
        void SetUniform(const std::string& name, const Vector2& value);
        void SetUniform(const std::string& name, const Vector3& value);
        void SetUniform(const std::string& name, const Vector4& value);
        void SetUniform(const std::string& name, const Matrix4x4& value);
        void SetUniform(const std::string& name, std::shared_ptr<Texture2D> texture, int slot = 0);

        // Reset all uniforms to their default values
        void ResetUniforms();

        // Get the Raylib shader ID
        unsigned int GetShaderID() const { return shader.id; }
        
        // Get the Raylib shader struct (for internal use)
        const ::Shader& GetRaylibShader() const { return shader; }

        // Check if shader is valid
        bool IsValid() const { return shader.id > 0; }

        // Static factory methods for common 2D shaders
        static std::shared_ptr<Shader> CreateDefault();
        static std::shared_ptr<Shader> CreateTinted();
        static std::shared_ptr<Shader> CreateDissolve();
        static std::shared_ptr<Shader> CreateOutline();

    private:
        ::Shader shader;
        std::unordered_map<std::string, int> uniformLocations;
        std::unordered_map<std::string, std::type_index> uniformTypes; // Track uniform types for proper reset

        // Get or cache uniform location
        int getUniformLocation(const std::string& name);
        
        // Reset a specific uniform to its default value
        void resetUniformToDefault(const std::string& name, std::type_index type);
    };
}
