#pragma once
#include <cstdint>
#include<gameEngine/gameEngine.hpp>

class Game {
private:
  GameEngine& engine;
  std::shared_ptr<SPhysics> physicsSystem;
  std::shared_ptr<SRender> renderSystem;

public:
  explicit Game(const WindowConfig& config) :
    engine(GameEngine::Instance(config, "Stayyy With Mee")) 
  {}

  void Init() {
    engine.Init();

    physicsSystem = engine.RegisterSystem<SPhysics, CGravity, CTransform, CRigidBody>();
    renderSystem = engine.RegisterSystem<SRender, CTransform, CSprite>();

    for (uint64_t i = 0; i < MAX_ENTITIES; i++) {
      float gravityY = 0.05f;
      float posX = (float)GetRandomValue(0, engine.GetConfig().rendering_width() - engine.GetConfig().blockSize);
      float posY = (float)GetRandomValue(0, engine.GetConfig().rendering_height() / 4);
      float size = (float)engine.GetConfig().blockSize / 4;

      engine.CreateEntity(
        "Falling Square",
        CGravity{.force = Vector2{0, gravityY}},
        CTransform{.position = Vector2{posX, posY}, .scale = Vector2{size, size}},
        CRigidBody{.velocity = Vector2{0.0f, 0.0f}, .acceleration = Vector2{0.0f, 0.0f}},
        CSprite{}
      );
    }
  }

  void Run() {
    while (!WindowShouldClose()) {
      physicsSystem->Update();

      engine.BeginFrame();
      renderSystem->Update();
      engine.EndFrame();
    }

    engine.Shutdown();
  }
};
