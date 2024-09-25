#include <Tsubasa/Node.h>
#include <Tsubasa/Application.h>
#include <algorithm>
#include <queue>

namespace Tsubasa
{
    Node::Node() : Client(application), Parent(parent), Children(children), Components(components), Transform(transform), LocalPosition(localPosition), LocalRotation(localRotation), LocalScale(localScale)
    {
        transform = Matrix4x4::Identity;
        localPosition = Vector3::Zero;
        localRotation = Quaternion::Identity;
        localScale = Vector3::One;
        dirty = false;
    }

    Node::~Node()
    {
        for (const auto &component : components)
        {
            component->OnDestroy();
        }
    }

    bool Node::SetParent(const std::shared_ptr<Node> &newParent)
    {
        if (parent != newParent && newParent != nullptr && newParent != shared_from_this())
        {
            if (parent != nullptr)
            {
                parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), shared_from_this()), parent->children.end());
            }
            application = newParent->application;
            parent = newParent;
            parent->children.push_back(shared_from_this());
            makeDirty();
            return true;
        }
        else
        {
            return false;
        }
    }

    const std::shared_ptr<Node> Node::AddChild(const std::shared_ptr<Node> &child)
    {
        if (child == nullptr)
        {
            std::shared_ptr<Node> newNode = std::make_shared<Node>();
            if (newNode->SetParent(shared_from_this()))
            {
                return newNode;
            }
            else
            {
                return nullptr;
            }
        }
        else
        {
            child->SetParent(shared_from_this());
            return child;
        }
    }

    bool Node::HasChild(const std::shared_ptr<Node> &child) const
    {
        return std::find(children.begin(), children.end(), child) != children.end();
    }

    const std::shared_ptr<Node> Node::RemoveChild(const std::shared_ptr<Node> &child)
    {
        auto it = std::find(children.begin(), children.end(), child);
        if (it != children.end())
        {
            children.erase(it);
            child->parent = nullptr;
            child->application = nullptr;
            return child;
        }
        return nullptr;
    }

    bool Node::HasComponent(const std::shared_ptr<Component> &component) const
    {
        return std::find(components.begin(), components.end(), component) != components.end();
    }

    const std::shared_ptr<Component> Node::RemoveComponent(const std::shared_ptr<Component> &component)
    {
        auto it = std::find(components.begin(), components.end(), component);
        if (it != components.end())
        {
            component->OnDestroy();
            components.erase(it);
            component->entity = nullptr;
            return component;
        }
        return nullptr;
    }

    void Node::Translate(const float &x, const float &y, const float &z, const Space &space)
    {
        if (space == Space::World)
        {
            SetWorldPosition(GetWorldPosition() + Vector3(x, y, z));
        }
        else
        {
            SetLocalPosition(LocalPosition + Vector3(x, y, z));
        }
    }
    
    void Node::Translate(const Vector3 &translation, const Space &space)
    {
        if (space == Space::World)
        {
            SetWorldPosition(GetWorldPosition() + translation);
        }
        else
        {
            SetLocalPosition(LocalPosition + translation);
        }
    }

    void Node::Rotate(const Quaternion &rotation, const Space &space)
    {
        if (space == Space::World)
        {
            SetWorldRotation(GetWorldRotation() * rotation);
        }
        else
        {
            SetLocalRotation(LocalRotation * rotation);
        }
    }

    void Node::Rotate(const float &x, const float &y, const float &z, const Space &space)
    {
        if (space == Space::World)
        {
            SetWorldRotation(GetWorldRotation() * Quaternion::FromEuler(x, y, z));
        }
        else
        {
            SetLocalRotation(LocalRotation * Quaternion::FromEuler(x, y, z));
        }
    }

    void Node::Rotate(const Vector3 &euler, const Space &space)
    {
        if (space == Space::World)
        {
            SetWorldRotation(GetWorldRotation() * Quaternion::FromEuler(euler));
        }
        else
        {
            SetLocalRotation(LocalRotation * Quaternion::FromEuler(euler));
        }
    }

    void Node::Scale(const float &x, const float &y, const float &z, const Space &space)
    {
        if (space == Space::World)
        {
            SetWorldScale(GetWorldScale() + Vector3(x, y, z));
        }
        else
        {
            SetLocalScale(LocalScale + Vector3(x, y, z));
        }
    }

    void Node::Scale(const Vector3 &scale, const Space &space)
    {
        if (space == Space::World)
        {
            SetWorldScale(GetWorldScale() + scale);
        }
        else
        {
            SetLocalScale(LocalScale + scale);
        }
    }

    void Node::SetLocalPosition(const float &x, const float &y, const float &z)
    {
        localPosition = Vector3(x, y, z);
        makeDirty();
    }

    void Node::SetLocalPosition(const Vector3 &position)
    {
        localPosition = position;
        makeDirty();
    }

    void Node::SetLocalRotation(const Quaternion &rotation)
    {
        localRotation = rotation;
        makeDirty();
    }

    void Node::SetLocalRotation(const float &x, const float &y, const float &z)
    {
        localRotation = Quaternion::FromEuler(x, y, z);
        makeDirty();
    }

    void Node::SetLocalRotation(const Vector3 &euler)
    {
        localRotation = Quaternion::FromEuler(euler);
        makeDirty();
    }

    void Node::SetLocalScale(const float &x, const float &y, const float &z)
    {
        localScale = Vector3(x, y, z);
        makeDirty();
    }

    void Node::SetLocalScale(const Vector3 &scale)
    {
        localScale = scale;
        makeDirty();
    }

    Vector3 Node::GetWorldPosition()
    {
        if (parent)
        {
            if (dirty)
            {
                updateTransform();
            }
            return transform * Vector3::Zero;
        }
        else
        {
            return LocalPosition;
        }
    }

    Vector3 Node::TransformPoint(const Vector3 &offset)
    {
        if (parent)
        {
            if (dirty)
            {
                updateTransform();
            }
            return transform * offset;
        }
        else
        {
            return LocalPosition + offset;
        }
    }

    void Node::SetWorldPosition(const float &x, const float &y, const float &z)
    {
        if (parent)
        {
            if (parent->dirty)
            {
                parent->updateTransform();
            }
            SetLocalPosition(parent->transform.Inversed() * Vector3(x, y, z));
        }
        else
        {
            SetLocalPosition(Vector3(x, y, z));
        }
    }

    void Node::SetWorldPosition(const Vector3 &position)
    {
        if (parent)
        {
            if (parent->dirty)
            {
                parent->updateTransform();
            }
            SetLocalPosition(parent->transform.Inversed() * position);
        }
        else
        {
            SetLocalPosition(position);
        }
    }

    Quaternion Node::GetWorldRotation() const
    {
        if (parent)
        {
            return parent->GetWorldRotation() * localRotation;
        }
        else
        {
            return localRotation;
        }
    }

    void Node::SetWorldRotation(const Quaternion &rotation)
    {
        if (parent)
        {
            SetLocalRotation(parent->GetWorldRotation().Inverse() * rotation);
        }
        else
        {
            SetLocalRotation(rotation);
        }
    }

    void Node::SetWorldRotation(const float &x, const float &y, const float &z)
    {
        if (parent)
        {
            SetLocalRotation(parent->GetWorldRotation().Inverse() * Quaternion::FromEuler(x, y, z));
        }
        else
        {
            SetLocalRotation(Quaternion::FromEuler(x, y, z));
        }
    }

    void Node::SetWorldRotation(const Vector3 &euler)
    {
        if (parent)
        {
            SetLocalRotation(parent->GetWorldRotation().Inverse() * Quaternion::FromEuler(euler));
        }
        else
        {
            SetLocalRotation(Quaternion::FromEuler(euler));
        }
    }

    Vector3 Node::GetWorldScale() const
    {
        if (parent)
        {
            return localScale * parent->GetWorldScale();
        }
        else
        {
            return localScale;
        }
    }

    void Node::SetWorldScale(const float &x, const float &y, const float &z)
    {
        if (parent)
        {
            const Vector3 &worldScale = parent->GetWorldScale();
            SetLocalScale(Vector3(x / worldScale.x, y / worldScale.y, z / worldScale.z));
        }
        else
        {
            SetLocalScale(Vector3(x, y, z));
        }
    }

    void Node::SetWorldScale(const Vector3 &scale)
    {
        if (parent)
        {
            SetLocalScale(scale / parent->GetWorldScale());
        }
        else
        {
            SetLocalScale(scale);
        }
    }

    void Node::Traverse(const std::function<void(const std::shared_ptr<Node> &node)> &callback)
    {
        std::queue<std::shared_ptr<Node>> queue;
        queue.push(shared_from_this());
        while (!queue.empty())
        {
            auto current = queue.front();
            queue.pop();
            callback(current);
            for (const auto &child : current->children)
            {
                queue.push(child);
            }
        }
    }

    void Node::makeDirty()
    {
        dirty = true;
        for (const auto &child : children)
        {
            child->makeDirty();
        }
    }

    void Node::updateTransform()
    {
        if (dirty)
        {
            if (parent)
            {
                if (parent->dirty)
                {
                    parent->updateTransform();
                }
                transform = Matrix4x4::TRS(LocalPosition, LocalRotation, LocalScale) * parent->Transform;
                // transform = Matrix4x4::Scale(LocalScale) * Matrix4x4::Rotate(LocalRotation) * Matrix4x4::Translate(LocalPosition) * parent->Transform;
            }
            else
            {
                transform = Matrix4x4::TRS(LocalPosition, LocalRotation, LocalScale);
                // transform = Matrix4x4::Scale(LocalScale) * Matrix4x4::Rotate(LocalRotation) * Matrix4x4::Translate(LocalPosition);
            }
            dirty = false;
        }
    }
}