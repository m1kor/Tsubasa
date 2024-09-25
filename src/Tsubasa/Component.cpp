#include <Tsubasa/Component.h>
#include <Tsubasa/Application.h>
#include <Tsubasa/Node.h>

namespace Tsubasa
{
    Component::Component() : Enabled(enabled), Entity(entity)
    {
        enabled = true;
    }

    Component::~Component() {}

    void Component::Enable()
    {
        if (!enabled)
        {
            enabled = true;
            OnEnable();
        }
    }

    void Component::Disable()
    {
        if (enabled)
        {
            enabled = false;
            OnDisable();
        }
    }

    void Component::SetEnabled(const bool &value)
    {
        if (value)
        {
            Enable();
        }
        else
        {
            Disable();
        }
    }

    void Component::OnInit() {}

    void Component::OnEnable() {}

    void Component::OnDisable() {}

    void Component::OnUpdate(float timeDelta) {}

    void Component::OnDestroy() {}
}