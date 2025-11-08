#pragma once
#include "core/colors.hpp"
#include "raylib.h"
#include <ComponentRegistry/physics/Physics.hpp>
#include <ComponentRegistry/render/Render.hpp>
#include <gameEngine/gameEngine.hpp>
#include <iostream>

class Game {
private:
  GameEngine &engine;

public:
  explicit Game(const WindowConfig &config)
      : engine(GameEngine::Instance(config, "Astroids", GRUVBOX_DARK0)) {}

  void Init() {
    engine.Init();
    std::cout << "Screen Width: " << engine.GetConfig().rendering_width()
              << "\nScreen Height:" << engine.GetConfig().rendering_height()
              << "\n";
    engine.CreateEntity("Space Ship",
                        CTransform{.position = Vector2{160.0f / 2, 160.0f / 2},
                                   .rotation = 12.0f},
                        CTriangle{6.0f});
  }

  void Run() { engine.Run(); }
};
