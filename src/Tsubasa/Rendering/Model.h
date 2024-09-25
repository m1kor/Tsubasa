#pragma once

#include <memory>
#include <string>

struct Model;

namespace Tsubasa
{
    enum class MeshType
    {
        Cube,
        Sphere,
        Plane,
        Custom
    };

    class Model
    {
        friend class MeshRenderer;
        friend class RaylibRenderSystem;
    public:
        Model(const MeshType &type = MeshType::Custom);
        Model(const std::string &path);
        ~Model();

        void Generate(const MeshType type);
        bool Load(const std::string &path);

        static std::shared_ptr<Model> FromPrimitive(const MeshType &type);
    private:
        std::shared_ptr<::Model> model;
    };
}