#include <Tsubasa/System.h>
#include <Tsubasa/Application.h>

namespace Tsubasa
{
    System::System() : Client(application) {}

    System::~System() {}

    void System::OnInit() {}

    bool System::OnUpdate(float timeDelta)
    {
        return true;
    }

    void System::OnExit() {}
}