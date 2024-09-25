#include <raylib/raylib.h>
#include <Tsubasa/Application.h>
#include <Tsubasa/Components/Camera.h>
#include <Tsubasa/Components/MeshRenderer.h>
#include <Tsubasa/Systems/RaylibRenderSystem.h>
#include <memory>
#include <iostream>
#include <raylib/raylib.h>

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
        if (active)
        {
            Entity->Translate(delta * timeDelta);
            Entity->Rotate(rotation);
            // Entity->Rotate(Tsubasa::Quaternion::AngleAxis(Tsubasa::Vector3(0.0f, 1.0f, 0.0f), timeDelta));
        }
        if (fix)
        {
            Entity->SetWorldRotation(Tsubasa::Quaternion::Identity);
            // Entity->SetWorldRotation(Tsubasa::Quaternion::FromTo(Entity->GetWorldPosition(), Tsubasa::Vector3::Zero));
            // Entity->SetWorldPosition(Tsubasa::Vector3::Zero);
        }
        // Entity->SetWorldPosition(Entity->GetWorldPosition());
    }
};

class TestApplication : public Tsubasa::Application
{
public:
    TestApplication() {}
    ~TestApplication() {}

    std::shared_ptr<Tsubasa::Node> cubeNode, secondNode, thirdNode, fourthNode;

    void OnStart() override
    {
        ActiveCamera = Root->AddChild()->AddComponent<Tsubasa::Camera>();
        ActiveCamera->Entity->SetWorldPosition(Tsubasa::Vector3(0.0f, 2.0f, 15.0f));

        // ActiveCamera->Entity->SetLocalRotation(Tsubasa::Quaternion::FromEuler(Tsubasa::Vector3(0.0f, 3.14159265359f, 0.0f)));
        // ActiveCamera->Entity->SetWorldRotation(Tsubasa::Quaternion::Look(Tsubasa::Vector3::Back, Tsubasa::Vector3::Up));
        // ActiveCamera->Entity->SetWorldRotation(Tsubasa::Quaternion::LookAt(ActiveCamera->Entity->GetWorldPosition(), Tsubasa::Vector3::Zero, Tsubasa::Vector3::Up));
        // ActiveCamera->Entity->SetWorldRotation(Tsubasa::Quaternion::AngleAxis(-ActiveCamera->Entity->GetWorldPosition().Normalized(), 0.0f));

        cubeNode = Root->AddChild(cubeNode);

        auto floor = Root->AddChild()->AddComponent<Tsubasa::MeshRenderer>(Tsubasa::Model::FromPrimitive(Tsubasa::MeshType::Plane));
        floor->Entity->SetWorldScale(Tsubasa::Vector3(10.0f, 1.0f, 10.0f));
        floor->Entity->SetWorldPosition(Tsubasa::Vector3::Down * 0.5f);

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
        ActiveCamera->Entity->SetWorldRotation(Tsubasa::Quaternion::LookAt(ActiveCamera->Entity->GetWorldPosition(), secondNode->GetWorldPosition(), Tsubasa::Vector3::Up));
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
            ActiveCamera->Entity->Translate(Tsubasa::Vector3::Forward * timeDelta * 2.0f);
        }
        if (IsKeyDown(KEY_DOWN))
        {
            ActiveCamera->Entity->Translate(Tsubasa::Vector3::Back * timeDelta * 2.0f);
        }
        if (IsKeyDown(KEY_LEFT))
        {
            ActiveCamera->Entity->Translate(Tsubasa::Vector3::Left * timeDelta * 2.0f);
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            ActiveCamera->Entity->Translate(Tsubasa::Vector3::Right * timeDelta * 2.0f);
        }
    }
};

int main(void)
{
    // std::shared_ptr<Tsubasa::Application> app = std::make_shared<TestApplication>();
    // Tsubasa::LaunchOptions options;
    // options.ScreenWidth = 1280;
    // options.ScreenHeight = 720;
    // options.Fullscreen = false;
    // options.VSync = true;
    // options.WindowTitle = "Test";
    // app->AddSystem(std::make_shared<Tsubasa::RaylibRenderSystem>(options));
    // app->Run();
    int width = 1280;
    int height = 720;
    InitWindow(width, height, "maze");
    float deltaX = 0;
    float deltaY = 0;
    while (!WindowShouldClose())
    {
        float timeDelta = GetFrameTime();
        deltaX = deltaX + 100 * timeDelta;
        deltaY = deltaY + 25 * timeDelta;
        while (deltaX > 48)
        {
            deltaX -= 48;
        }
        while (deltaY > 48)
        {
            deltaY -= 48;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        int depth = 5;
        for (int x = -2; x < width / 48 + 2; x++)
        {
            for (int y = -2; y < height / 48 + 2; y++)
            {
                float rx = x * 48 + deltaX;
                float ry = y * 48 + deltaY;
                for (int z = 0; z < depth; z++)
                {
                    float alphaFactor = 1 - z / (float)depth;
                    alphaFactor *= alphaFactor;
                    rx -= (rx - width / 2) * 0.02;
                    ry -= (ry - height / 2) * 0.02;
                    // draw_rectangle_lines_ex(Rectangle(rx, ry, 24, 24), 3, Color(0, 128, 255, int(255 * alphaFactor)))
                    DrawRectangleLinesEx(Rectangle{rx, ry, 24, 24}, 3, Color{0, 128, 255, (unsigned char)(255 * alphaFactor)});
                }
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
