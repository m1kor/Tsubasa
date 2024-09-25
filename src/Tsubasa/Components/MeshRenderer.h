#pragma once

#include <Tsubasa/Component.h>
#include <Tsubasa/Rendering/Model.h>
#include <memory>

namespace Tsubasa
{
    class MeshRenderer : public Component
    {
    public:
        MeshRenderer(std::shared_ptr<Model> model = nullptr);
        ~MeshRenderer();

        std::shared_ptr<Model> RenderModel;
    };
}