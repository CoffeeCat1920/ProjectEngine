#pragma once
#include <gameEngine/gameEngine.hpp>

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

    engine.Shutdown();
  }
};
