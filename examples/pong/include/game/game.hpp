#pragma once
#include "ComponentRegistry/physics/Physics.hpp"
#include "ComponentRegistry/render/Render.hpp"
#include <gameEngine/gameEngine.hpp>
#include <random>

class Game {
private:
  GameEngine &engine;

public:
  explicit Game(const WindowConfig &config)
      : engine(GameEngine::Instance(config, "Falling Boxes")) {}

  void CreateRandomFallingBoxes(GameEngine &engine, int count = 2048) {
    const float width = engine.GetConfig().rendering_width();
    const float height = engine.GetConfig().rendering_height();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posX(0.0f, width);
    std::uniform_real_distribution<float> posY(0.0f, height);
    std::uniform_real_distribution<float> velY(-2.0f, 2.0f);
    std::uniform_real_distribution<float> size(5.0f, 25.0f);

    for (int i = 0; i < count; ++i) {
      float x = posX(gen);
      float y = posY(gen);
      float s = size(gen);
      float vy = velY(gen);

      engine.CreateEntity("Falling Boxes", CGravity{.force = {0.0f, 0.1f}},
                          CTransform{.position = {x, y}, .scale = {s, s}},
                          CRigidBody{.velocity = {0.0f, vy}}, CRectangle{s, s});
    }
  }

  void Init() {
    engine.Init();
    CreateRandomFallingBoxes(engine);
  }

  void Run() { engine.Run(); }
};
