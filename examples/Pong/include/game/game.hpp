#pragma once

#include "../components/components.hpp"
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
    engine.CreateEntity(
        "PlayerA",
        CTransform{.position = Vector2{engine.GetConfig().blockSize * 1.0f,
                                       engine.GetConfig().blockSize * 4.0f},
                   .rotation = 12.0f},
        CRectangle{.w = (float)engine.GetConfig().blockSize,
                   .h = (float)engine.GetConfig().blockSize * 2},
        CPlayerA{});

    engine.CreateEntity(
        "PlayerB",
        CTransform{.position = Vector2{engine.GetConfig().blockSize * 18.0f,
                                       engine.GetConfig().blockSize * 4.0f},
                   .rotation = 12.0f},
        CRectangle{.w = (float)engine.GetConfig().blockSize,
                   .h = (float)engine.GetConfig().blockSize * 2},
        CPlayerB{});
  }

  void Run() { engine.Run(); }
};
