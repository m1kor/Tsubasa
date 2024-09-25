#include <Tsubasa/Rendering/Model.h>
#include <raylib/raylib.h>

namespace Tsubasa
{
    Model::Model(const MeshType &type)
    {
        if (type == MeshType::Custom)
        {
            model = std::make_shared<::Model>();
        }
        else
        {
            Generate(type);
        }
    }

    Model::Model(const std::string &path)
    {
        Load(path);
    }

    Model::~Model() {}

    void Model::Generate(const MeshType type)
    {
        switch (type)
        {
        case MeshType::Cube:
            model = std::make_shared<::Model>(LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f)));
            break;
        case MeshType::Sphere:
            model = std::make_shared<::Model>(LoadModelFromMesh(GenMeshSphere(0.5f, 16, 16)));
            break;
        case MeshType::Plane:
            model = std::make_shared<::Model>(LoadModelFromMesh(GenMeshPlane(1.0f, 1.0f, 1, 1)));
            break;
        default:
            break;
        }
    }

    bool Model::Load(const std::string &path)
    {
        model = std::make_shared<::Model>(LoadModel(path.c_str()));
        return model != nullptr;
    }

    std::shared_ptr<Model> Model::FromPrimitive(const MeshType &type)
    {
        return std::make_shared<Model>(type);
    }
}