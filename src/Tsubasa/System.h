#pragma once

#include <memory>

namespace Tsubasa
{
    class Application;

    class System
    {
        friend class Application;
    public:
        System();
        ~System();

        virtual void OnInit();
        virtual bool OnUpdate(float timeDelta);
        virtual void OnStop();
        virtual void OnExit();

        std::shared_ptr<Application> GetClient() const;

    private:
        std::weak_ptr<Application> application;
    };
}
