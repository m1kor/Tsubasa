#include <Tsubasa/Systems/RaylibRenderSystem.h>
#include <Tsubasa/Application.h>
#include <Tsubasa/Components/MeshRenderer.h>
#include <raylib/raylib.h>
#include <raylib/rlgl.h>
#include <math.h>

namespace Tsubasa
{
    RaylibRenderSystem::RaylibRenderSystem()
    {
        Options.ScreenWidth = 1920;
        Options.ScreenHeight = 1080;
        Options.WindowTitle = "Tsubasa Engine";
        Options.Fullscreen = true;
        Options.VSync = true;
    }

    RaylibRenderSystem::RaylibRenderSystem(LaunchOptions options)
    {
        Options = options;
    }

    RaylibRenderSystem::~RaylibRenderSystem() {}

    void RaylibRenderSystem::OnInit()
    {
        unsigned int flags = 0;
        if (Options.Fullscreen)
        {
            flags |= FLAG_FULLSCREEN_MODE;
        }
        if (Options.VSync)
        {
            flags |= FLAG_VSYNC_HINT;
        }
        SetConfigFlags(flags);
        InitWindow(Options.ScreenWidth, Options.ScreenHeight, Options.WindowTitle.c_str());
        SetExitKey(KEY_NULL);
    }

    bool RaylibRenderSystem::OnUpdate(float timeDelta)
    {
        if (WindowShouldClose())
        {
            return false;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);
        if (Client->ActiveCamera != nullptr && Client->ActiveCamera->Entity != nullptr)
        {
            beginMode3D(Client->ActiveCamera);
            Client->Root->Traverse<MeshRenderer>([this](const std::shared_ptr<MeshRenderer> &meshRenderer)
                                                 {
                if (meshRenderer->Enabled)
                {
                    renderModel(meshRenderer);
                } });
            EndMode3D();
        }
        EndDrawing();
        return true;
    }

    void RaylibRenderSystem::OnExit()
    {
        CloseWindow();
    }

    void RaylibRenderSystem::beginMode3D(std::shared_ptr<Camera> camera)
    {
        rlDrawRenderBatchActive(); // Update and draw internal render batch

        rlMatrixMode(RL_PROJECTION); // Switch to projection matrix
        rlPushMatrix();              // Save previous matrix, which contains the settings for the 2d ortho projection
        rlLoadIdentity();            // Reset current matrix (projection)

        float aspect = GetRenderWidth() / (float)GetRenderHeight();

        // NOTE: zNear and zFar values are important when computing depth buffer values
        if (camera->Projection == CameraProjection::Perspective)
        {
            // Setup perspective projection
            double top = RL_CULL_DISTANCE_NEAR * tan(camera->FieldOfView * 0.5f * DEG2RAD);
            double right = top * aspect;

            rlFrustum(-right, right, -top, top, RL_CULL_DISTANCE_NEAR, RL_CULL_DISTANCE_FAR);
        }
        else if (camera->Projection == CameraProjection::Orthographic)
        {
            // Setup orthographic projection
            double top = camera->FieldOfView / 2.0f;
            double right = top * aspect;

            rlOrtho(-right, right, -top, top, RL_CULL_DISTANCE_NEAR, RL_CULL_DISTANCE_FAR);
        }

        rlMatrixMode(RL_MODELVIEW); // Switch back to modelview matrix
        rlLoadIdentity();           // Reset current matrix (modelview)

        // Setup Camera view
        Matrix4x4 matView = Matrix4x4::LookAt(camera->Entity->GetWorldPosition(), camera->Entity->TransformPoint(Vector3::Forward), camera->Entity->GetWorldRotation() * Vector3::Up).Transposed();
        rlMultMatrixf(matView.m); // Multiply modelview matrix by view matrix (camera)

        rlEnableDepthTest(); // Enable DEPTH_TEST for 3D
    }

    void RaylibRenderSystem::renderModel(std::shared_ptr<MeshRenderer> meshRenderer)
    {
        if (meshRenderer->RenderModel != nullptr && meshRenderer->RenderModel->model != nullptr)
        {
            for (int i = 0; i < meshRenderer->RenderModel->model->meshCount; i++)
            {
                ::Matrix transform;
                transform.m0 = meshRenderer->Entity->Transform.m[0];
                transform.m1 = meshRenderer->Entity->Transform.m[1];
                transform.m2 = meshRenderer->Entity->Transform.m[2];
                transform.m3 = meshRenderer->Entity->Transform.m[3];
                transform.m4 = meshRenderer->Entity->Transform.m[4];
                transform.m5 = meshRenderer->Entity->Transform.m[5];
                transform.m6 = meshRenderer->Entity->Transform.m[6];
                transform.m7 = meshRenderer->Entity->Transform.m[7];
                transform.m8 = meshRenderer->Entity->Transform.m[8];
                transform.m9 = meshRenderer->Entity->Transform.m[9];
                transform.m10 = meshRenderer->Entity->Transform.m[10];
                transform.m11 = meshRenderer->Entity->Transform.m[11];
                transform.m12 = meshRenderer->Entity->Transform.m[12];
                transform.m13 = meshRenderer->Entity->Transform.m[13];
                transform.m14 = meshRenderer->Entity->Transform.m[14];
                transform.m15 = meshRenderer->Entity->Transform.m[15];
                DrawMesh(meshRenderer->RenderModel->model->meshes[i], meshRenderer->RenderModel->model->materials[meshRenderer->RenderModel->model->meshMaterial[i]], transform);
                // Vector3 position = Entity->GetWorldPosition();
                // DrawCubeWires(::Vector3{position.x, position.y, position.z}, 1.0f, 1.0f, 1.0f, RED);
                // position = Entity->TransformPoint(Vector3::Forward * 0.5f);
                // DrawCubeWires(::Vector3{position.x, position.y, position.z}, 0.5f, 0.5f, 0.5f, GREEN);
                // position = Entity->TransformPoint(Vector3::Up * 0.5f);
                // DrawCubeWires(::Vector3{position.x, position.y, position.z}, 0.5f, 0.5f, 0.5f, BLUE);
            }
        }
    }
}