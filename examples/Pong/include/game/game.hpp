#pragma once

#include "core/colors.hpp"
#include "raylib.h"
#include <ComponentRegistry/physics/Physics.hpp>
#include <ComponentRegistry/render/Render.hpp>
#include <gameEngine/gameEngine.hpp>

class Game {
private:
  GameEngine &engine;

public:
  explicit Game(const WindowConfig &config)
      : engine(GameEngine::Instance(config, "Astroids", BACKGROUND)) {}

  void Init() {
    engine.Init();
    engine.CreateEntity(
        "Space Ship",
        CTransform{.position = Vector2{engine.GetConfig().blockSize * 1.0f,
                                       engine.GetConfig().blockSize * 4.0f},
                   .rotation = 12.0f},
        CRectangle{.w = (float)engine.GetConfig().blockSize,
                   .h = (float)engine.GetConfig().blockSize * 2});
  }

  void Run() { engine.Run(); }
};
