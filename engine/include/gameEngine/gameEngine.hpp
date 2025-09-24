#pragma once
#include "core/colors.hpp"
#include <core/setting.hpp>
#include <ECS/ECS.h>
#include <ECS/system/system.hpp>
#include <ECS/entity/entity.hpp>
#include <ECS/component/component.hpp>
#include <cameraController/cameraController.hpp>
#include <raylib.h>
#include <string>

constexpr int DEFAULT_SCALE = 4;

struct WindowConfig {
  int blockSize = 32;
  int width = 10;
  int height = 6;
  int scale = DEFAULT_SCALE;

  WindowConfig() = default;
  WindowConfig(int block, int w, int h, int s = DEFAULT_SCALE)
    : blockSize(block),
      width(w),
      height(h),
      scale(s) {}

  int rendering_width() const {
    return width * blockSize * scale;
  }

  int rendering_height() const {
    return height * blockSize * scale;
  }
};

inline ECS gEcs;

struct CGravity {
  Vector2 force;
};

struct CRigidBody {
  Vector2 velocity;
  Vector2 acceleration;
};

struct CTransform {
  Vector2 position;
  Vector2 scale;
};

struct SPhysics : System {
  void Update() {
    for (const auto& entity : System::entities) {
      auto& rigidBody = gEcs.GetComponent<CRigidBody>(entity);
      auto& transform = gEcs.GetComponent<CTransform>(entity);
      auto const& gravity = gEcs.GetComponent<CGravity>(entity);

      transform.position.x += rigidBody.velocity.x;
      transform.position.y += rigidBody.velocity.y;

      rigidBody.velocity.x += gravity.force.x;
      rigidBody.velocity.y += gravity.force.y;
    }
  }
};

struct SRender : System {
  void Update() {
    for (const auto& entity : System::entities) {
      auto& transform = gEcs.GetComponent<CTransform>(entity);
      DrawRectangle(
        (int)transform.position.x,
        (int)transform.position.y,
        (int)transform.scale.x,
        (int)transform.scale.y,
        GRUVBOX_RED
      );
    }
  }
};

class GameEngine {
private:
  const WindowConfig windowConfig;
  const std::string title = "Window";
  CameraController cameraController;

  EntityVec entities;

public:
  GameEngine(std::string title = "title")
    : title(title) {}

  explicit GameEngine(const WindowConfig& config, std::string title = "title")
    : windowConfig(config),
      title(title),
      cameraController(windowConfig.scale) {}

  void Init() {}

  void Run() {
    // Register components
    gEcs.RegisterComponent<CGravity>();
    gEcs.RegisterComponent<CRigidBody>();
    gEcs.RegisterComponent<CTransform>();

    const ComponentId cGravity = gEcs.GetComponentId<CGravity>();
    const ComponentId cRigidBody = gEcs.GetComponentId<CGravity>();
    const ComponentId cTransform = gEcs.GetComponentId<CGravity>();

    auto sPhysics = gEcs.RegisterSystem<SPhysics>();
    auto sRender = gEcs.RegisterSystem<SRender>();

    gEcs.SetSystemSignature<SPhysics> ({cGravity, cTransform, cRigidBody}); 
    gEcs.SetSystemSignature<SRender> ({cGravity, cTransform, cRigidBody}); 

    entities.resize(MAX_ENTITIES);

    for (auto& entity : entities) {
      entity = gEcs.AddEntity("Falling Square");

      // Unique gravity per entity
      float gravityY = 0.1f + (float)GetRandomValue(1, 4) * 0.05f;


      // Random position inside the window
      float posX = (float)GetRandomValue(0, windowConfig.rendering_width() - windowConfig.blockSize);
      float posY = (float)GetRandomValue(0, windowConfig.rendering_height() / 4); // spawn near top

      // Slightly varied scale
      float size = (float)((float)windowConfig.blockSize / 4 + GetRandomValue(0, windowConfig.blockSize / 8));

      // Random initial velocity
      float velX = (float)GetRandomValue(-2, 2) * 0.5f;
      float velY = (float)GetRandomValue(-1, 1) * 0.5f;

      gEcs.AddComponent(
        entity,
        CGravity{ .force = Vector2{0, gravityY} },
        CTransform{
          .position = Vector2{posX, posY},
          .scale = Vector2{size, size}
        },
        CRigidBody{
          .velocity = Vector2{velX, velY},
          .acceleration = Vector2{0.0f, 0.0f}
        }
      );
    }

    InitWindow(windowConfig.rendering_width(), windowConfig.rendering_height(), title.c_str());
    SetTargetFPS(60);


    while (!WindowShouldClose()) {
      sPhysics->Update();

      BeginDrawing();
      ClearBackground(BACKGROUND);

      BeginMode2D(cameraController.GetCamera());
      sRender->Update();
      EndMode2D();

      // --- FPS Counter ---
      int fps = GetFPS();
      std::string fpsText = "FPS: " + std::to_string(fps);

      int textWidth = MeasureText(fpsText.c_str(), 20); // font size 20
      DrawText(
        fpsText.c_str(),
        windowConfig.rendering_width() - textWidth - 10, 
        10,                                              
        20,                                              
        GRUVBOX_AQUA
      );

      EndDrawing();
    }

    CloseWindow();
  }
};
