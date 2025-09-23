#include "ECS/entity/entity.hpp"
#include "ECS/system/system.hpp"
#include "core/setting.hpp"
#include <core/colors.hpp>
#include <cstdint>
#include <iostream>
#include <raylib.h>
#include <gameEngine/gameEngine.hpp>
#include <string>


struct CTransform {
  Vector2 position = {0, 0};
  Vector2 direction = {0, 0};
  float velocity = 0.0f;
  CTransform() = default; 
  CTransform(Vector2 position, float velocity = 0.0f) : 
    position(position), 
    direction(Vector2{0, 1}),
    velocity(velocity)
  {}
};

struct CShape {
  float width = 0, height = 0;
  CShape() = default;
  CShape(float w, float h) :
    width(w),
    height(h)
  {}
};

void GameEngine::SMovement() {
  const EntityVec& entities = ecs.GetEntities<CTransform>();
  for (const auto& entity : entities) {
    auto& transform = ecs.GetComponent<CTransform>(entity);
    transform.position.x += transform.velocity * transform.direction.x;
    transform.position.y += transform.velocity * transform.direction.y;
  }
}

void GameEngine::SRender() {
  const EntityVec& entities = ecs.GetEntities<CTransform, CShape>();
  for (const auto& entity : entities) {
    const auto& transform = ecs.GetComponent<CTransform>(entity);
    const auto& shape = ecs.GetComponent<CShape>(entity); 
    DrawRectangle(transform.position.x, transform.position.y, 
        shape.width, shape.height, GRUVBOX_RED);
  }
}


struct SRec : System {
  SRec(EntityVec entitites) :
    System(entitites)
  {}

  void Do() const override {
    std::cout << "Test" << std::endl;
  }
};

void GameEngine::Update() {
  ecs.GetSystem<SRec>()->Do();
  SMovement();
}

void GameEngine::Draw() {
  SRender();
}


void GameEngine::Init() {
  ecs.RegisterComponent<CTransform>();
  ecs.RegisterComponent<CShape>();
  ecs.RegisterSystem<SRec>();

  for (uint64_t i = 0; i < MAX_ENTITIES; i++) {
    Entity e = ecs.AddEntity("Test" + std::to_string(i));
    CTransform t({(float)(i * 3), 0}, 3.0f);
    CShape s((float)windowConfig.blockSize/4, (float)windowConfig.blockSize/4);
    ecs.AddComponent(e, t);
    ecs.AddComponent(e, s);
  }
}

void GameEngine::Run() {
  InitWindow(windowConfig.rendering_width(), windowConfig.rendering_height(), title.c_str());

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    std::cout << "FPS: " << GetFPS() << std::endl;

    Update();
    BeginDrawing();
    BeginMode2D(cameraController.GetCamera());
    ClearBackground(BACKGROUND);
    Draw();
    EndMode2D();
    EndDrawing();
  }

  CloseWindow();
}
