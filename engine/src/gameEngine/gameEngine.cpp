#include <core/colors.hpp>
#include <raylib.h>
#include <gameEngine/gameEngine.hpp>
#include <string>

void GameEngine::Draw() {
  SRender();
}


struct CTransform {
  Vector2 position = {0, 0};
  Vector2 direction = {0, 0};
  float velocity = 0.0f;
  CTransform() = default; 
  CTransform(Vector2 position, float velocity = 0.0f) : 
    position(position), 
    velocity(velocity)
  {}
};


void GameEngine::Update() {
  SMovement();
}

void GameEngine::SMovement() {
  auto& component = ecs.GetComponent<CTransform>(e);
  component.position.x += component.velocity;
}

void GameEngine::SRender() {
  auto& component = ecs.GetComponent<CTransform>(e);
  DrawRectangle(component.position.x, component.position.y, 
      windowConfig.blockSize, windowConfig.blockSize, GRUVBOX_RED);
}

void GameEngine::Init() {
  e = ecs.AddEntity("Test"); 

  CTransform t({0, 0}, 12.0f);

  ecs.RegisterComponent<CTransform>();
  ecs.AddComponent(e, t);
}

void GameEngine::Run() {
  InitWindow(windowConfig.rendering_width(), windowConfig.rendering_height(), title.c_str());

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
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
