#pragma once
#include <ComponentRegistry/physics/Physics.hpp>
#include <ComponentRegistry/render/Render.hpp>
#include <gameEngine/gameEngine.hpp>

class Game {
private:
  GameEngine &engine;

public:
  explicit Game(const WindowConfig &config)
      : engine(GameEngine::Instance(config, "Falling Boxes")) {}

  void Init() { engine.Init(); }

  void Run() { engine.Run(); }
};
