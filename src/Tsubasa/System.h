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
        virtual void OnExit();

        const std::shared_ptr<Application> &Client;

    private:
        std::shared_ptr<Application> application;
    };
}