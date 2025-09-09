#pragma once

#include <Tsubasa/Assets/AssetRegistry.h>
#include <Tsubasa/Components/Camera.h>
#include <Tsubasa/Node.h>
#include <Tsubasa/System.h>
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
        virtual void OnStop();
        virtual void OnExit();

        std::shared_ptr<Camera> ActiveCamera;

        const std::shared_ptr<Node> &Root;

        const std::list<std::shared_ptr<System>> &Systems;

        AssetRegistry &GetAssetRegistry() const;

    private:
        bool running;
        std::shared_ptr<Node> root;
        std::list<std::shared_ptr<System>> systems;
        std::unique_ptr<AssetRegistry> assetRegistry;
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
        else if (system->GetClient() != shared_from_this())
        {
            auto client = system->GetClient();
            if (client != nullptr)
            {
                client->RemoveSystem(system);
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
