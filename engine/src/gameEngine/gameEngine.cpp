#include <core/colors.hpp>
#include <raylib.h>
#include <gameEngine/gameEngine.hpp>

void GameEngine::Update() {}
void GameEngine::Draw() {}
void GameEngine::Init() {
  auto e = entityManager.CreateEntity(); 
  entityManager.AddTag(e, "Player");
}

void GameEngine::Run() {
  InitWindow(windowConfig.rendering_width(), windowConfig.rendering_height(), title.c_str());

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    Update();
    BeginDrawing();
    BeginMode2D(cameraController.GetCamera());
    ClearBackground(GRUVBOX_DARK2);
    Draw();
    EndDrawing();
  }

  CloseWindow();
}
