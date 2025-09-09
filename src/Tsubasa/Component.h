#pragma once

#include <memory>

namespace Tsubasa
{
    class Node;
    class Application;

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
        std::shared_ptr<Node> GetEntity() const;
        std::shared_ptr<Application> GetApplication() const;

    private:
        bool enabled;
        std::weak_ptr<Node> entity;
    };
}
