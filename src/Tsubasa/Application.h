#pragma once

#include <Tsubasa/Node.h>
#include <Tsubasa/System.h>
#include <Tsubasa/Components/Camera.h>
#include <list>
#include <memory>
#include <string>

namespace Tsubasa
{
    class Application : public std::enable_shared_from_this<Application>
    {
    public:
        Application();
        ~Application();

        template <typename T>
        const std::shared_ptr<T> AddSystem(const std::shared_ptr<T> &system);
        template <typename T, typename... Args>
        const std::shared_ptr<T> AddSystem(Args... args);
        bool HasSystem(const std::shared_ptr<System> &system) const;
        const std::shared_ptr<System> RemoveSystem(const std::shared_ptr<System> &system);
        template <typename T>
        std::shared_ptr<T> GetSystem()
        {
            for (auto &system : systems)
            {
                if (std::dynamic_pointer_cast<T>(system))
                {
                    return std::dynamic_pointer_cast<T>(system);
                }
            }
            return nullptr;
        }
        void Run();

        virtual void OnInit();
        virtual void OnStart();
        virtual void OnUpdate(float timeDelta);
        virtual void OnExit();

        std::shared_ptr<Camera> ActiveCamera;

        const std::shared_ptr<Node> &Root;

        const std::list<std::shared_ptr<System>> &Systems;

    private:
        bool running;
        std::shared_ptr<Node> root;
        std::list<std::shared_ptr<System>> systems;
    };

    template <typename T>
    const std::shared_ptr<T> Application::AddSystem(const std::shared_ptr<T> &system)
    {
        if (system == nullptr)
        {
            std::shared_ptr<T> newSystem = std::make_shared<T>();
            newSystem->application = shared_from_this();
            systems.push_back(newSystem);
            if (running)
            {
                newSystem->OnInit();
            }
            return newSystem;
        }
        else if (system->Client != shared_from_this())
        {
            if (system->Client != nullptr)
            {
                system->Client->RemoveSystem(system);
            }
            system->application = shared_from_this();
            systems.push_back(system);
            if (running)
            {
                system->OnInit();
            }
            return system;
        }
        else
        {
            return nullptr;
        }
    }

    template <typename T, typename... Args>
    const std::shared_ptr<T> Application::AddSystem(Args... args)
    {
        std::shared_ptr<T> newSystem = std::make_shared<T>(args...);
        newSystem->entity = shared_from_this();
        systems.push_back(newSystem);
        if (running)
        {
            newSystem->OnInit();
        }
        return newSystem;
    }
}