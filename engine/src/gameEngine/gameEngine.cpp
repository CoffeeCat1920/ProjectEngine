#include <core/colors.hpp>
#include <raylib.h>
#include <gameEngine/gameEngine.hpp>
#include <string>

void GameEngine::Update() {}
void GameEngine::Draw() {}

struct CTransform {
  Vector2 position = {0, 0};
  Vector2 durection = {0, 0};
  float velocity = 0.0f;
  CTransform() = default; 
  CTransform(Vector2 position) : 
    position(position) 
  {}
};

void GameEngine::Init() {
  auto e = entityManager.CreateEntity(); 
  entityManager.AddTag(e, "Player");

  CTransform t({0, 0});

  componentManager.RegisterComponent<CTransform>();
  componentManager.AddComponent(e, t);
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
    EndDrawing();
  }

  CloseWindow();
}
