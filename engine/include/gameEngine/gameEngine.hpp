#pragma once

#include "core/colors.hpp"
#include <core/setting.hpp>
#include <ECS/ECS.h>
#include <ECS/system/system.hpp>
#include <ECS/entity/entity.hpp>
#include <ECS/component/component.hpp>
#include <cameraController/cameraController.hpp>
#include <cstdint>
#include <iostream>
#include <raylib.h>
#include <string>

constexpr int DEFAULT_SCALE = 4;

struct WindowConfig {
  int blockSize = 32;      
  int width = 10;           
  int height = 6;           
  int scale = DEFAULT_SCALE;

  WindowConfig() = default;
  WindowConfig(int block, int w, int h, int s = DEFAULT_SCALE) : 
    blockSize(block), 
    width(w), 
    height(h), 
    scale(s) 
  {}

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
    for (const auto& entity : System::entities ) {
      std::cout << "Ecs:" << entity;
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
    for ( const auto& entity : System::entities ) {
      std::cout << "Ecs:" << entity;
      auto& transform = gEcs.GetComponent<CTransform>(entity);
      DrawRectangle(transform.position.x, transform.position.y, transform.scale.x, transform.scale.y, GRUVBOX_RED);
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
  GameEngine(std::string title = "title") :
    title(title)
  {}

  explicit GameEngine(const WindowConfig& config, std::string title = "title") : 
    windowConfig(config),
    title(title),
    cameraController(windowConfig.scale)
  {}

  void Init() {
    gEcs.RegisterComponent<CGravity>(); 
    gEcs.RegisterComponent<CRigidBody>();
    gEcs.RegisterComponent<CTransform>();
    
    entities.resize(MAX_ENTITIES);

    uint64_t x = 0;

    for (auto& entity : entities) {
      entity = gEcs.AddEntity("Falling Square");

      gEcs.AddComponent(
        entity,
        CGravity{ .force = Vector2{0, -1} }
      );

      gEcs.AddComponent(
        entity,
        CTransform {
          .position = Vector2 { (float) windowConfig.blockSize * x, (float) windowConfig.blockSize * 0 },
          .scale = Vector2 { (float) windowConfig.blockSize/4, (float) windowConfig.blockSize/4 }
        }
      );

      gEcs.AddComponent(
        entity,
        CRigidBody {
          .velocity = Vector2{0.0f, 0.0f},
          .acceleration = Vector2{0.0f, 0.0f}
        }
      );

    }

  }

  void Run() {

  InitWindow(windowConfig.rendering_width(), windowConfig.rendering_height(), title.c_str());

  SetTargetFPS(60);

  Signature signature;
  signature.set(gEcs.GetComponentId<CGravity>());
  signature.set(gEcs.GetComponentId<CRigidBody>());
  signature.set(gEcs.GetComponentId<CTransform>());

  auto sPhysics = gEcs.RegisterSystem<SPhysics>();
  auto sRender = gEcs.RegisterSystem<SRender>();

  gEcs.SetSystemSignature<SPhysics>(signature);
  gEcs.SetSystemSignature<SRender>(signature);

  while (!WindowShouldClose()) {
    sPhysics->Update();
    sRender->Update();
    BeginDrawing();
    BeginMode2D(cameraController.GetCamera());
    ClearBackground(BACKGROUND);
    EndMode2D();
    EndDrawing();
  }

  CloseWindow();
  }
};
