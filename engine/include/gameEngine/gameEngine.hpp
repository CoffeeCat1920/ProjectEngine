#pragma once
#include "core/colors.hpp"
#include <core/setting.hpp>
#include <ECS/ECS.h>
#include <ECS/system/system.hpp>
#include <ECS/entity/entity.hpp>
#include <ECS/component/component.hpp>
#include <cameraController/cameraController.hpp>
#include <filesystem>
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

struct CSprite {
  Texture2D texture = LoadTexture("./assets/icon.png");
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
      auto& sprite = gEcs.GetComponent<CSprite>(entity);
      auto& transform = gEcs.GetComponent<CTransform>(entity);
      DrawTexture(sprite.texture, transform.position.x, transform.position.y, WHITE);
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
    InitWindow(windowConfig.rendering_width(), windowConfig.rendering_height(), title.c_str());
    SetTargetFPS(60);

    // Register components
    gEcs.RegisterComponent<CGravity>();
    gEcs.RegisterComponent<CRigidBody>();
    gEcs.RegisterComponent<CTransform>();
    gEcs.RegisterComponent<CSprite>();

    auto sPhysics = gEcs.RegisterSystem<SPhysics>();
    auto sRender = gEcs.RegisterSystem<SRender>();

    gEcs.SetSystemSignature<SPhysics, CGravity, CTransform, CRigidBody>(); 
    gEcs.SetSystemSignature<SRender, CTransform, CSprite>(); 

    entities.resize(MAX_ENTITIES);

    for (auto& entity : entities) {
      entity = gEcs.AddEntity("Falling Square");

      // Fixed gravity
      float gravityY = 0.2f;

      // Random spawn position
      float posX = (float)GetRandomValue(0, windowConfig.rendering_width() - windowConfig.blockSize);
      float posY = (float)GetRandomValue(0, windowConfig.rendering_height() / 4);

      // Fixed size
      float size = (float)windowConfig.blockSize / 4;

      // Fixed velocity
      float velX = 0.0f;
      float velY = 0.0f;

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
        },
        CSprite{}
      );
    }


    while (!WindowShouldClose()) {
      sPhysics->Update();

      BeginDrawing();
      ClearBackground(BACKGROUND);

      BeginMode2D(cameraController.GetCamera());
      sRender->Update();
      EndMode2D();

      // FPS counter
      int fps = GetFPS();
      std::string fpsText = "FPS: " + std::to_string(fps);

      int textWidth = MeasureText(fpsText.c_str(), 20);
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
