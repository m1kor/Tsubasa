#pragma once

#include <functional>
#include <initializer_list>
#include <memory>
#include <vector>
#include <Tsubasa/Component.h>
#include <Tsubasa/Math/Matrix4x4.h>
#include <Tsubasa/Math/Vector3.h>
#include <Tsubasa/Math/Quaternion.h>

namespace Tsubasa
{
    enum class Space
    {
        World,
        Local
    };

    class Application;

    class Node : public std::enable_shared_from_this<Node>
    {
        friend class Application;
    public:
        Node();
        ~Node();

        // Hierarchichy
        bool SetParent(const std::shared_ptr<Node> &newParent);
        const std::shared_ptr<Node> AddChild(const std::shared_ptr<Node> &child = nullptr);
        bool HasChild(const std::shared_ptr<Node> &child) const;
        const std::shared_ptr<Node> RemoveChild(const std::shared_ptr<Node> &child);
        // Components
        template <typename T>
        const std::shared_ptr<T> AddComponent(const std::shared_ptr<T> &component);
        template <typename T, typename... Args>
        const std::shared_ptr<T> AddComponent(Args... args);
        bool HasComponent(const std::shared_ptr<Component> &component) const;
        const std::shared_ptr<Component> RemoveComponent(const std::shared_ptr<Component> &component);
        template <typename T>
        std::shared_ptr<T> GetComponent()
        {
            for (auto &component : components)
            {
                if (std::dynamic_pointer_cast<T>(component))
                {
                    return std::dynamic_pointer_cast<T>(component);
                }
            }
            return nullptr;
        }
        // Local space
        void Translate(const float &x, const float &y, const float &z, const Space &space = Space::Local);
        void Translate(const Vector3 &translation, const Space &space = Space::Local);
        void Rotate(const Quaternion &rotation, const Space &space = Space::Local);
        void Rotate(const float &x, const float &y, const float &z, const Space &space = Space::Local);
        void Rotate(const Vector3 &euler, const Space &space = Space::Local);
        void Scale(const float &x, const float &y, const float &z, const Space &space = Space::Local);
        void Scale(const Vector3 &scale, const Space &space = Space::Local);
        void SetLocalPosition(const float &x, const float &y, const float &z);
        void SetLocalPosition(const Vector3 &position);
        void SetLocalRotation(const Quaternion &rotation);
        void SetLocalRotation(const float &x, const float &y, const float &z);
        void SetLocalRotation(const Vector3 &euler);
        void SetLocalScale(const float &x, const float &y, const float &z);
        void SetLocalScale(const Vector3 &scale);
        // World space
        Vector3 GetWorldPosition();
        Vector3 TransformPoint(const Vector3 &offset);
        void SetWorldPosition(const float &x, const float &y, const float &z);
        void SetWorldPosition(const Vector3 &position);
        Quaternion GetWorldRotation() const;
        void SetWorldRotation(const Quaternion &rotation);
        void SetWorldRotation(const float &x, const float &y, const float &z);
        void SetWorldRotation(const Vector3 &euler);
        Vector3 GetWorldScale() const;
        void SetWorldScale(const float &x, const float &y, const float &z);
        void SetWorldScale(const Vector3 &scale);
        // Traverse
        void Traverse(const std::function<void(const std::shared_ptr<Node> &node)> &callback);
        template <typename T>
        void Traverse(const std::function<void(const std::shared_ptr<T> &node)> &callback)
        {
            Traverse([callback](const std::shared_ptr<Node> &node)
                     {
                auto component = node->GetComponent<T>();
                if (component != nullptr)
                {
                    callback(component);
                }
            });
        }

        const std::shared_ptr<Node> &Parent;
        const std::vector<std::shared_ptr<Node>> &Children;
        std::vector<std::shared_ptr<Component>> &Components;

        const std::shared_ptr<Application> &Client;
        const Vector3 &LocalPosition;
        const Quaternion &LocalRotation;
        const Vector3 &LocalScale;
        const Matrix4x4 &Transform;

    private:
        std::shared_ptr<Application> application;
        std::shared_ptr<Node> parent;
        std::vector<std::shared_ptr<Node>> children;
        std::vector<std::shared_ptr<Component>> components;
        bool dirty;
        Matrix4x4 transform;
        Vector3 localPosition;
        Quaternion localRotation;
        Vector3 localScale;

        void makeDirty();
        void updateTransform();
    };

    template <typename T>
    const std::shared_ptr<T> Node::AddComponent(const std::shared_ptr<T> &component)
    {
        if (component == nullptr)
        {
            std::shared_ptr<T> newComponent = std::make_shared<T>();
            newComponent->entity = shared_from_this();
            components.push_back(newComponent);
            newComponent->OnInit();
            return newComponent;
        }
        else if (component->Entity != shared_from_this())
        {
            if (component->Entity != nullptr)
            {
                component->Entity->RemoveComponent(component);
            }
            component->entity = shared_from_this();
            components.push_back(component);
            component->OnInit();
            return component;
        }
        else
        {
            return nullptr;
        }
    }

    template <typename T, typename... Args>
    const std::shared_ptr<T> Node::AddComponent(Args... args)
    {
        std::shared_ptr<T> newComponent = std::make_shared<T>(args...);
        newComponent->entity = shared_from_this();
        components.push_back(newComponent);
        newComponent->OnInit();
        return newComponent;
    }
}