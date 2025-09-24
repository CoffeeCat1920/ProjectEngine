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


class GameEngine {
private:
  const WindowConfig windowConfig;
  const std::string title = "Window";
  CameraController cameraController;

public:
  GameEngine(std::string title = "title")
    : title(title) {}

  explicit GameEngine(const WindowConfig& config, std::string title = "title")
    : windowConfig(config),
      title(title),
      cameraController(windowConfig.scale) {}

  void Init() {
    InitWindow(windowConfig.rendering_width(), windowConfig.rendering_height(), title.c_str());
    SetTargetFPS(60);

    // Register default components
    gEcs.RegisterComponent<CGravity>();
    gEcs.RegisterComponent<CRigidBody>();
    gEcs.RegisterComponent<CTransform>();
    gEcs.RegisterComponent<CSprite>();
  }

  // Utility for adding a new entity with components
  template<typename... Components>
  Entity CreateEntity(const std::string& name, Components&&... comps) {
    Entity entity = gEcs.AddEntity(name);
    gEcs.AddComponent(entity, std::forward<Components>(comps)...);
    return entity;
  }

  // Utility for registering a system and setting its signature
  template<typename TSystem, typename... Components>
  std::shared_ptr<TSystem> RegisterSystem() {
    auto system = gEcs.RegisterSystem<TSystem>();
    gEcs.SetSystemSignature<TSystem, Components...>();
    return system;
  }

  void BeginFrame() {
    BeginDrawing();
    ClearBackground(BACKGROUND);
    BeginMode2D(cameraController.GetCamera());
  }

  void EndFrame() {
    EndMode2D();

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

  void Shutdown() {
    CloseWindow();
  }

  WindowConfig GetConfig() {
    return windowConfig;
  }
};
