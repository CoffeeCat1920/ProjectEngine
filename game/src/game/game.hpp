#pragma once
#include <cstdint>
#include <gameEngine/gameEngine.hpp>
#include <iostream>

class Game {
private:
  GameEngine &engine;

public:
  explicit Game(const WindowConfig &config)
      : engine(GameEngine::Instance(config, "Stayyy With Mee")) {}

  void Init() {
    engine.Init();
    engine.LoadScene("./assets/scene.json");
  }

  void Run() {
    while (!WindowShouldClose()) {
      engine.BeginFrame();
      engine.EndFrame();
    }
  }
};
