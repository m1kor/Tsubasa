#include <Tsubasa/Application.h>
#include <Tsubasa/Assets/Sources/FileAssetSource.h>
#include <Tsubasa/Math/Matrix4x4.h>
#include <algorithm>
#include <chrono>

namespace Tsubasa
{
    Application::Application() : Root(root), Systems(systems)
    {
        running = false;
        root = std::make_shared<Node>();
        ActiveCamera = nullptr;
        assetRegistry = std::make_unique<AssetRegistry>();
        assetRegistry->AddAssetSource(std::make_unique<FileAssetSource>("./assets/"));
    }

    Application::~Application() = default;

    bool Application::HasSystem(const std::shared_ptr<System> &system) const
    {
        return std::find(systems.begin(), systems.end(), system) != systems.end();
    }

    const std::shared_ptr<System> Application::RemoveSystem(const std::shared_ptr<System> &system)
    {
        auto it = std::find(systems.begin(), systems.end(), system);
        if (it != systems.end())
        {
            system->OnExit();
            systems.erase(it);
            system->application.reset();
            return system;
        }
        return nullptr;
    }

    void Application::Run()
    {
        Root->application = shared_from_this();
        OnInit();
        for (const auto &system : systems)
        {
            system->OnInit();
        }
        OnStart();
        float timeDelta = 0.0f;
        running = true;
        while (running)
        {
            auto begin = std::chrono::high_resolution_clock::now();
            // Component->OnUpdate
            Root->Traverse([timeDelta](const std::shared_ptr<Node> &node)
                           {
                for (const auto &component : node->Components)
                {
                    if (component->Enabled)
                    {
                        component->OnUpdate(timeDelta);
                    }
                } });
            // Calculate transforms
            Root->Traverse([](const std::shared_ptr<Node> &node)
                           {
                // node->transform = Matrix4x4::Scale(node->LocalScale) * Matrix4x4::Rotate(node->LocalRotation) * Matrix4x4::Translate(node->LocalPosition);
                if (node->dirty)
                {
                    auto nodeParent = node->GetParent();
                    if (nodeParent)
                    {
                        node->transform = Matrix4x4::TRS(node->LocalPosition, node->LocalRotation, node->LocalScale) * nodeParent->Transform;
                    }
                    else
                    {
                        node->transform = Matrix4x4::TRS(node->LocalPosition, node->LocalRotation, node->LocalScale);
                    }
                    node->dirty = false;
                } });
            // System->OnUpdate
            for (const auto &system : systems)
            {
                if (!system->OnUpdate(timeDelta))
                {
                    running = false;
                }
            }
            // Application->OnUpdate
            OnUpdate(timeDelta);
            auto end = std::chrono::high_resolution_clock::now();
            timeDelta = std::chrono::duration<float>(end - begin).count();
        }
        Root->Traverse([](const std::shared_ptr<Node> &node)
                       {
            for (const auto &component : node->Components)
            {
                component->OnDestroy();
            } });

        for (const auto &system : systems)
        {
            system->OnStop();
        }
        OnStop();

        // First collect all nodes to avoid traversal issues
        std::vector<std::shared_ptr<Node>> allNodes;
        Root->Traverse([&allNodes](const std::shared_ptr<Node> &node)
                       { allNodes.push_back(node); });

        // Clear all references from all nodes
        for (auto &node : allNodes)
        {
            node->Components.clear();
            const_cast<Node *>(node.get())->children.clear();
            const_cast<Node *>(node.get())->parent.reset();
        }

        root.reset();
        allNodes.clear();
        assetRegistry.reset();

        for (const auto &system : systems)
        {
            system->OnExit();
        }

        systems.clear();
        OnExit();
    }

    void Application::OnInit() {}

    void Application::OnStart() {}

    void Application::OnUpdate(float timeDelta) {}

    void Application::OnStop() {}

    void Application::OnExit() {}

    AssetRegistry &Application::GetAssetRegistry() const
    {
        return *assetRegistry;
    }
}
