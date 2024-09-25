#pragma once

#include <memory>

namespace Tsubasa
{
    class Node;

    class Component
    {
        friend class Node;

    public:
        Component();
        ~Component();

        void Enable();
        void Disable();
        void SetEnabled(const bool &value);

        virtual void OnInit();
        virtual void OnEnable();
        virtual void OnDisable();
        virtual void OnUpdate(float timeDelta);
        virtual void OnDestroy();

        const bool &Enabled;
        const std::shared_ptr<Node> &Entity;

    private:
        bool enabled;
        std::shared_ptr<Node> entity;
    };
}