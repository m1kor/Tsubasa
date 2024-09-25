#include <Tsubasa/Components/MeshRenderer.h>
#include <Tsubasa/Node.h>
#include <raylib/raylib.h>

namespace Tsubasa
{
    MeshRenderer::MeshRenderer(std::shared_ptr<Model> model)
    {
        if (model != nullptr)
        {
            RenderModel = model;
        }
        else
        {
            RenderModel = std::make_shared<Model>();
        }
    }

    MeshRenderer::~MeshRenderer() {}
}