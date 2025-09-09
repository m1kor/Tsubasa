#include <Tsubasa/System.h>
#include <Tsubasa/Application.h>

namespace Tsubasa
{
    System::System() {}

    System::~System() = default;

    void System::OnInit() {}

    bool System::OnUpdate(float timeDelta)
    {
        return true;
    }

    void System::OnStop() {}

    void System::OnExit() {}

    std::shared_ptr<Application> System::GetClient() const
    {
        return application.lock();
    }
}
