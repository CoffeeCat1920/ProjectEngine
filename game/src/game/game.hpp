#pragma once
#include <cstdint>
#include<gameEngine/gameEngine.hpp>

struct SPhysics : System {
  void Update() {
    for (const auto& entity : System::entities) {
      auto& rigidBody = gEcs.GetComponent<CRigidBody>(entity);
      auto& transform = gEcs.GetComponent<CTransform>(entity);
      auto const& gravity = gEcs.GetComponent<CGravity>(entity);

      transform.position.x += rigidBody.velocity.x;
      transform.position.y += rigidBody.velocity.y;

      rigidBody.velocity.x += gravity.force.x;
      rigidBody.velocity.y += gravity.force.y;
    }
  }
};

struct SRender : System {
  void Update() {
    for (const auto& entity : System::entities) {
      auto& sprite = gEcs.GetComponent<CSprite>(entity);
      auto& transform = gEcs.GetComponent<CTransform>(entity);
      DrawTexture(sprite.texture, transform.position.x, transform.position.y, WHITE);
    }
  }
};

class Game {
private:
  GameEngine engine;
  std::shared_ptr<SPhysics> physicsSystem;
  std::shared_ptr<SRender> renderSystem;

public:
  explicit Game(const WindowConfig& config)
    : engine(config, "My ECS Game") {}

  void Init() {
    engine.Init();

    physicsSystem = engine.RegisterSystem<SPhysics, CGravity, CTransform, CRigidBody>();
    renderSystem = engine.RegisterSystem<SRender, CTransform, CSprite>();

    // Create entities
    for (uint64_t i = 0; i < MAX_ENTITIES; i++) {
      float gravityY = 0.2f;
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
