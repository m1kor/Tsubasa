#include <Tsubasa/Systems/RaylibRenderSystem.h>
#include <Tsubasa/Application.h>
#include <Tsubasa/Components/MeshRenderer.h>
#include <Tsubasa/Components/SpriteRenderer.h>
#include <raylib/raylib.h>
#include <raylib/rlgl.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <unordered_map>

namespace Tsubasa
{
    struct SpriteInstanceData
    {
        Vector3 Position;
        Vector3 Scale;
        float Rotation;
        Vector2 Pivot;
        std::shared_ptr<SpriteRenderer> Renderer;
    };

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

    RaylibRenderSystem::~RaylibRenderSystem() = default;

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
        auto client = GetClient();
        if (client && client->ActiveCamera != nullptr && client->ActiveCamera->GetEntity() != nullptr)
        {
            beginMode3D(client->ActiveCamera);
            client->Root->Traverse<MeshRenderer>([this](const std::shared_ptr<MeshRenderer> &meshRenderer)
                                                 {
                if (meshRenderer->Enabled)
                {
                    renderModel(meshRenderer);
                } });
            EndMode3D();
        }

        // Enable depth testing for sprites
        rlEnableDepthTest();

        // Collect and batch sprites by texture for instanced rendering
        std::unordered_map<unsigned int, std::vector<SpriteInstanceData>> spriteBatches;

        if (client) {
            client->Root->Traverse<SpriteRenderer>([&spriteBatches](const std::shared_ptr<SpriteRenderer> &spriteRenderer)
                                               {
            if (spriteRenderer->Enabled && spriteRenderer->Texture != nullptr)
            {
                unsigned int textureId = spriteRenderer->Texture->texture.id;
                auto entity = spriteRenderer->GetEntity();
                if (!entity) return;
                Vector3 worldPos = entity->GetWorldPosition();
                Vector3 scale = entity->GetWorldScale();
                float rotation = entity->GetWorldRotation().Euler().z * RAD2DEG;
                
                spriteBatches[textureId].push_back(SpriteInstanceData{
                    worldPos,
                    scale, 
                    rotation,
                    spriteRenderer->Pivot,
                    spriteRenderer
                });
            } });
        }

        // Render each texture batch as instanced quads
        for (const auto &batch : spriteBatches)
        {
            renderSpriteBatch(batch.first, batch.second);
        }

        // Disable depth testing after sprite rendering
        rlDisableDepthTest();

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
        auto cameraEntity = camera->GetEntity();
        if (!cameraEntity) return;
        Matrix4x4 matView = Matrix4x4::LookAt(cameraEntity->GetWorldPosition(), cameraEntity->TransformPoint(Vector3::Forward), cameraEntity->GetWorldRotation() * Vector3::Up).Transposed();
        rlMultMatrixf(matView.m); // Multiply modelview matrix by view matrix (camera)

        rlEnableDepthTest(); // Enable DEPTH_TEST for 3D
    }

    void RaylibRenderSystem::renderModel(std::shared_ptr<MeshRenderer> meshRenderer)
    {
        if (meshRenderer->RenderModel != nullptr && meshRenderer->RenderModel->model != nullptr)
        {
            auto entity = meshRenderer->GetEntity();
            if (!entity) return;
            for (int i = 0; i < meshRenderer->RenderModel->model->meshCount; i++)
            {
                ::Matrix transform;
                transform.m0 = entity->Transform.m[0];
                transform.m1 = entity->Transform.m[1];
                transform.m2 = entity->Transform.m[2];
                transform.m3 = entity->Transform.m[3];
                transform.m4 = entity->Transform.m[4];
                transform.m5 = entity->Transform.m[5];
                transform.m6 = entity->Transform.m[6];
                transform.m7 = entity->Transform.m[7];
                transform.m8 = entity->Transform.m[8];
                transform.m9 = entity->Transform.m[9];
                transform.m10 = entity->Transform.m[10];
                transform.m11 = entity->Transform.m[11];
                transform.m12 = entity->Transform.m[12];
                transform.m13 = entity->Transform.m[13];
                transform.m14 = entity->Transform.m[14];
                transform.m15 = entity->Transform.m[15];
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

    void RaylibRenderSystem::renderSprite(std::shared_ptr<SpriteRenderer> spriteRenderer)
    {
        if (spriteRenderer->Texture != nullptr)
        {
            auto entity = spriteRenderer->GetEntity();
            if (!entity) return;
            Vector3 worldPos = entity->GetWorldPosition();
            Vector3 scale = entity->GetWorldScale();

            float rotation = entity->GetWorldRotation().Euler().z * RAD2DEG;

            ::Rectangle sourceRect = {0, 0, (float)spriteRenderer->Texture->texture.width, (float)spriteRenderer->Texture->texture.height};

            // Calculate sprite dimensions
            float spriteWidth = sourceRect.width * scale.x;
            float spriteHeight = sourceRect.height * scale.y;

            // Calculate pivot offset
            float pivotOffsetX = spriteWidth * spriteRenderer->Pivot.x;
            float pivotOffsetY = spriteHeight * spriteRenderer->Pivot.y;

            // Use rlPushMatrix/rlPopMatrix to handle transformations in 3D space
            rlPushMatrix();
            rlTranslatef(worldPos.x, worldPos.y, worldPos.z); // Use full 3D position including Z
            rlRotatef(rotation, 0.0f, 0.0f, 1.0f);
            rlTranslatef(-pivotOffsetX, -pivotOffsetY, 0.0f);

            // Draw the sprite as a textured quad in 3D space
            rlSetTexture(spriteRenderer->Texture->texture.id);
            rlBegin(RL_QUADS);
            rlColor4ub(255, 255, 255, 255);
            rlNormal3f(0.0f, 0.0f, 1.0f);

            // Bottom-left
            rlTexCoord2f(0.0f, 1.0f);
            rlVertex3f(0.0f, spriteHeight, 0.0f);

            // Bottom-right
            rlTexCoord2f(1.0f, 1.0f);
            rlVertex3f(spriteWidth, spriteHeight, 0.0f);

            // Top-right
            rlTexCoord2f(1.0f, 0.0f);
            rlVertex3f(spriteWidth, 0.0f, 0.0f);

            // Top-left
            rlTexCoord2f(0.0f, 0.0f);
            rlVertex3f(0.0f, 0.0f, 0.0f);
            rlEnd();
            rlSetTexture(0);

            rlPopMatrix();
        }
    }

    void RaylibRenderSystem::renderSpriteBatch(unsigned int textureId, const std::vector<SpriteInstanceData> &instances)
    {
        if (instances.empty())
            return;

        // Set texture once for entire batch
        rlSetTexture(textureId);

        // Get texture dimensions from the first instance for UV calculations
        const auto &firstInstance = instances[0];
        float textureWidth = (float)firstInstance.Renderer->Texture->texture.width;
        float textureHeight = (float)firstInstance.Renderer->Texture->texture.height;

        // Begin batch rendering
        rlBegin(RL_QUADS);
        rlColor4ub(255, 255, 255, 255);
        rlNormal3f(0.0f, 0.0f, 1.0f);

        // Render all instances in this batch
        for (const auto &instance : instances)
        {
            // Calculate sprite dimensions
            float spriteWidth = textureWidth * instance.Scale.x;
            float spriteHeight = textureHeight * instance.Scale.y;

            // Calculate pivot offset
            float pivotOffsetX = spriteWidth * instance.Pivot.x;
            float pivotOffsetY = spriteHeight * instance.Pivot.y;

            // Calculate rotation matrix components
            float cosRot = cosf(instance.Rotation * DEG2RAD);
            float sinRot = sinf(instance.Rotation * DEG2RAD);

            // Define quad vertices relative to pivot
            float vertices[4][2] = {
                {-pivotOffsetX, spriteHeight - pivotOffsetY},              // Bottom-left
                {spriteWidth - pivotOffsetX, spriteHeight - pivotOffsetY}, // Bottom-right
                {spriteWidth - pivotOffsetX, -pivotOffsetY},               // Top-right
                {-pivotOffsetX, -pivotOffsetY}                             // Top-left
            };

            // UV coordinates
            float uvs[4][2] = {
                {0.0f, 1.0f}, // Bottom-left
                {1.0f, 1.0f}, // Bottom-right
                {1.0f, 0.0f}, // Top-right
                {0.0f, 0.0f}  // Top-left
            };

            // Render the quad with rotation and translation
            for (int i = 0; i < 4; i++)
            {
                // Apply rotation
                float rotatedX = vertices[i][0] * cosRot - vertices[i][1] * sinRot;
                float rotatedY = vertices[i][0] * sinRot + vertices[i][1] * cosRot;

                // Apply translation
                float finalX = rotatedX + instance.Position.x;
                float finalY = rotatedY + instance.Position.y;

                rlTexCoord2f(uvs[i][0], uvs[i][1]);
                rlVertex3f(finalX, finalY, instance.Position.z);
            }
        }

        rlEnd();
        rlSetTexture(0);
    }
}
