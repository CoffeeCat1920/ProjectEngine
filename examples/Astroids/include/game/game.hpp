#pragma once
#include "../system/system.hpp"
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
    engine.CreateEntity("Space Ship",
                        CTransform{.position = Vector2{160.0f / 2, 160.0f / 2},
                                   .rotation = 12.0f},
                        CIsoTriangle{.base = 30, .height = 33});
  }

  void Run() { engine.Run(); }
};
