#include <raylib/raylib.h>
#include <Tsubasa/Application.h>
#include <Tsubasa/Core/Graphics/Texture2D.h>
#include <Tsubasa/Core/Graphics/Shader.h>
#include <Tsubasa/Components/Camera.h>
#include <Tsubasa/Components/MeshRenderer.h>
#include <Tsubasa/Components/SpriteRenderer.h>
#include <Tsubasa/Systems/RaylibRenderSystem.h>
#include <memory>
#include <iostream>

using namespace std;

class MoveComponent : public Tsubasa::Component
{
public:
    Tsubasa::Vector3 delta;
    Tsubasa::Quaternion rotation;
    bool active;
    bool fix;

    void OnInit() override
    {
        fix = false;
        active = false;
        rotation = Tsubasa::Quaternion::Identity;
    }

    void OnUpdate(float timeDelta) override
    {
        auto entity = GetEntity();
        if (entity && active)
        {
            entity->Translate(delta * timeDelta);
            entity->Rotate(rotation);
            // entity->Rotate(Tsubasa::Quaternion::AngleAxis(Tsubasa::Vector3(0.0f, 1.0f, 0.0f), timeDelta));
        }
        if (entity && fix)
        {
            entity->SetWorldRotation(Tsubasa::Quaternion::Identity);
            // entity->SetWorldRotation(Tsubasa::Quaternion::FromTo(entity->GetWorldPosition(), Tsubasa::Vector3::Zero));
            // entity->SetWorldPosition(Tsubasa::Vector3::Zero);
        }
        // Entity->SetWorldPosition(Entity->GetWorldPosition());
    }
};

class TestApplication : public Tsubasa::Application
{
public:
    TestApplication() = default;
    ~TestApplication() = default;

    std::shared_ptr<Tsubasa::Node> cubeNode, secondNode, thirdNode, fourthNode;
    std::shared_ptr<Tsubasa::Node> logoNode, additionalNode, toodaSoodaNode;

    void OnStart() override
    {
        ActiveCamera = Root->AddChild()->AddComponent<Tsubasa::Camera>();
        ActiveCamera->GetEntity()->SetWorldPosition(Tsubasa::Vector3(0.0f, 2.0f, 15.0f));

        // ActiveCamera->Entity->SetLocalRotation(Tsubasa::Quaternion::FromEuler(Tsubasa::Vector3(0.0f, 3.14159265359f, 0.0f)));
        // ActiveCamera->Entity->SetWorldRotation(Tsubasa::Quaternion::Look(Tsubasa::Vector3::Back, Tsubasa::Vector3::Up));
        // ActiveCamera->Entity->SetWorldRotation(Tsubasa::Quaternion::LookAt(ActiveCamera->Entity->GetWorldPosition(), Tsubasa::Vector3::Zero, Tsubasa::Vector3::Up));
        // ActiveCamera->Entity->SetWorldRotation(Tsubasa::Quaternion::AngleAxis(-ActiveCamera->Entity->GetWorldPosition().Normalized(), 0.0f));

        auto texture = GetAssetRegistry().Load<Tsubasa::Texture2D>("logo.png");
        auto sprite = std::make_shared<Tsubasa::SpriteMaterial>(texture);
        sprite->Tint = Tsubasa::Vector4(1.0f, 0.5f, 0.5f, 1.0f);
        auto spriteBlue = std::make_shared<Tsubasa::SpriteMaterial>(texture);
        spriteBlue->Tint = Tsubasa::Vector4(0.5f, 0.5f, 1.0f, 1.0f);
        logoNode = Root->AddChild();
        logoNode->AddComponent(std::make_shared<Tsubasa::SpriteRenderer>(sprite));
        logoNode->SetWorldPosition(Tsubasa::Vector3(500.0f, 300.0f, 0.0f));
        additionalNode = logoNode->AddChild();
        additionalNode->AddComponent(std::make_shared<Tsubasa::SpriteRenderer>(spriteBlue));
        additionalNode->Translate(Tsubasa::Vector3::Right * 128.0f);

        cubeNode = Root->AddChild(cubeNode);

        auto floor = Root->AddChild()->AddComponent<Tsubasa::MeshRenderer>(Tsubasa::Model::FromPrimitive(Tsubasa::MeshType::Plane));
        floor->GetEntity()->SetWorldScale(Tsubasa::Vector3(10.0f, 1.0f, 10.0f));
        floor->GetEntity()->SetWorldPosition(Tsubasa::Vector3::Down * 0.5f);

        cubeNode->AddComponent(std::make_shared<MoveComponent>());
        cubeNode->AddComponent(std::make_shared<Tsubasa::MeshRenderer>(Tsubasa::Model::FromPrimitive(Tsubasa::MeshType::Sphere)));
        cubeNode->GetComponent<MoveComponent>()->active = true;
        // cubeNode->GetComponent<MoveComponent>()->delta = Tsubasa::Vector3(0.5f, 0.0f, 0.0f);
        cubeNode->GetComponent<MoveComponent>()->rotation = Tsubasa::Quaternion::AngleAxis(Tsubasa::Vector3(0.0f, 1.0f, 0.0f), 0.003f);

        secondNode = cubeNode->AddChild();
        secondNode->AddComponent(std::make_shared<MoveComponent>());
        secondNode->AddComponent(std::make_shared<Tsubasa::MeshRenderer>(Tsubasa::Model::FromPrimitive(Tsubasa::MeshType::Cube)));
        secondNode->GetComponent<MoveComponent>()->active = false;
        // secondNode->GetComponent<MoveComponent>()->delta = Tsubasa::Vector3(0.0f, 1.0f, 0.0f);
        secondNode->GetComponent<MoveComponent>()->rotation = Tsubasa::Quaternion::Identity;
        secondNode->Translate(Tsubasa::Vector3::Right * 3.0f);
        // secondNode->GetComponent<MoveComponent>()->fix = true;

        thirdNode = secondNode->AddChild();
        thirdNode->AddComponent(std::make_shared<MoveComponent>());
        thirdNode->AddComponent(std::make_shared<Tsubasa::MeshRenderer>(Tsubasa::Model::FromPrimitive(Tsubasa::MeshType::Cube)));
        thirdNode->Translate(Tsubasa::Vector3::Up * 3.0f);
        thirdNode->GetComponent<MoveComponent>()->active = false;
        thirdNode->GetComponent<MoveComponent>()->fix = true;

        fourthNode = thirdNode->AddChild();
        fourthNode->AddComponent(std::make_shared<MoveComponent>());
        fourthNode->AddComponent(std::make_shared<Tsubasa::MeshRenderer>(Tsubasa::Model::FromPrimitive(Tsubasa::MeshType::Cube)));
        fourthNode->Translate(Tsubasa::Vector3::Up * 2.0f);
        fourthNode->GetComponent<MoveComponent>()->active = true;
        fourthNode->GetComponent<MoveComponent>()->delta = Tsubasa::Vector3(0.0f, 0.3f, 0.0f);
        fourthNode->GetComponent<MoveComponent>()->rotation = Tsubasa::Quaternion::AngleAxis(Tsubasa::Vector3(0.0f, 1.0f, 0.0f), 0.003f);
    }

    void OnUpdate(float timeDelta) override
    {
        ActiveCamera->GetEntity()->SetWorldRotation(Tsubasa::Quaternion::LookAt(ActiveCamera->GetEntity()->GetWorldPosition(), fourthNode->GetWorldPosition(), Tsubasa::Vector3::Up));
        // if (IsKeyPressed(KEY_SPACE))
        // {
        //     cubeNode->GetComponent<MoveComponent>()->active = !cubeNode->GetComponent<MoveComponent>()->active;
        // }
        // if (IsKeyDown(KEY_LEFT))
        // {
        //     cubeNode->Translate(Tsubasa::Vector3::Left * timeDelta * 2.0f);
        // }
        if (IsKeyDown(KEY_UP))
        {
            ActiveCamera->GetEntity()->Translate(Tsubasa::Vector3::Forward * timeDelta * 2.0f);
        }
        if (IsKeyDown(KEY_DOWN))
        {
            ActiveCamera->GetEntity()->Translate(Tsubasa::Vector3::Back * timeDelta * 2.0f);
        }
        if (IsKeyDown(KEY_LEFT))
        {
            ActiveCamera->GetEntity()->Translate(Tsubasa::Vector3::Left * timeDelta * 2.0f);
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            ActiveCamera->GetEntity()->Translate(Tsubasa::Vector3::Right * timeDelta * 2.0f);
        }
        logoNode->Rotate(Tsubasa::Quaternion::AngleAxis(Tsubasa::Vector3::Back, timeDelta));
    }
};

class ShaderExampleApplication : public Tsubasa::Application
{
public:
    ShaderExampleApplication() = default;
    ~ShaderExampleApplication() = default;

    std::shared_ptr<Tsubasa::Node> defaultSpriteNode, tintedSpriteNode, outlineNode;

    void OnStart() override
    {
        ActiveCamera = Root->AddChild()->AddComponent<Tsubasa::Camera>();
        ActiveCamera->GetEntity()->SetWorldPosition(Tsubasa::Vector3(0.0f, 0.0f, 5.0f));

        // Load a texture
        auto texture = GetAssetRegistry().Load<Tsubasa::Texture2D>("logo.png");

        // Create sprite with default shader
        auto defaultMaterial = std::make_shared<Tsubasa::SpriteMaterial>(texture);
        defaultSpriteNode = Root->AddChild();
        defaultSpriteNode->AddComponent(std::make_shared<Tsubasa::SpriteRenderer>(defaultMaterial));
        defaultSpriteNode->SetWorldPosition(Tsubasa::Vector3(200.0f, 200.0f, 0.0f));

        // Create sprite with tinted shader
        auto tintedShader = Tsubasa::Shader::CreateTinted();
        auto tintedMaterial = std::make_shared<Tsubasa::SpriteMaterial>(texture, Tsubasa::Vector4(1.0f, 1.0f, 1.0f, 1.0f), tintedShader);
        tintedMaterial->SetVector4("tintColor", Tsubasa::Vector4(1.0f, 0.5f, 0.2f, 1.0f)); // Orange tint
        tintedSpriteNode = Root->AddChild();
        tintedSpriteNode->AddComponent(std::make_shared<Tsubasa::SpriteRenderer>(tintedMaterial));
        tintedSpriteNode->SetWorldPosition(Tsubasa::Vector3(400.0f, 200.0f, 0.0f));

        // Create sprite with outline shader
        auto outlineShader = Tsubasa::Shader::CreateOutline();
        auto outlineMaterial = std::make_shared<Tsubasa::SpriteMaterial>(texture, Tsubasa::Vector4(1.0f, 1.0f, 1.0f, 1.0f), tintedShader);
        outlineMaterial->SetVector4("tintColor", Tsubasa::Vector4(0.5f, 0.5f, 1.0f, 1.0f)); // Light blue tint
        // outlineMaterial->SetVector4("outlineColor", Tsubasa::Vector4(0.0f, 1.0f, 0.0f, 1.0f)); // Green outline
        // outlineMaterial->SetFloat("outlineWidth", 2.0f);
        // outlineMaterial->SetVector2("textureSize", Tsubasa::Vector2(128.0f, 128.0f)); // Assuming logo is 128x128
        outlineNode = Root->AddChild();
        outlineNode->AddComponent(std::make_shared<Tsubasa::SpriteRenderer>(outlineMaterial));
        outlineNode->SetWorldPosition(Tsubasa::Vector3(600.0f, 200.0f, 0.0f));
    }

    void OnUpdate(float timeDelta) override
    {
        // Rotate sprites to show them in action
        defaultSpriteNode->Rotate(Tsubasa::Quaternion::AngleAxis(Tsubasa::Vector3::Back, timeDelta * 0.5f));
        tintedSpriteNode->Rotate(Tsubasa::Quaternion::AngleAxis(Tsubasa::Vector3::Forward, timeDelta * 0.8f));
        outlineNode->Rotate(Tsubasa::Quaternion::AngleAxis(Tsubasa::Vector3::Back, timeDelta * 0.3f));
    }
};

int main(void)
{
    std::shared_ptr<Tsubasa::Application> app = std::make_shared<ShaderExampleApplication>();
    Tsubasa::LaunchOptions options;
    options.ScreenWidth = 1280;
    options.ScreenHeight = 720;
    options.Fullscreen = false;
    options.VSync = true;
    options.WindowTitle = "Test";
    app->AddSystem(std::make_shared<Tsubasa::RaylibRenderSystem>(options));
    app->Run();
    return 0;
}
