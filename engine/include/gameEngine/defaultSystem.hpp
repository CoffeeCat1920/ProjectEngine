#pragma once

#include "ECS/ECS.h"
#include <ECS/system/baseSystem.hpp>
#include <gameEngine/defaultComponent.hpp> 

struct SPhysics : System {
  ECS& gEcs = ECS::Instance();
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
  ECS& gEcs = ECS::Instance();
  void Update() {
    for (const auto& entity : System::entities) {
      auto& sprite = gEcs.GetComponent<CSprite>(entity);
      auto& transform = gEcs.GetComponent<CTransform>(entity);
      DrawTexture(sprite.texture, transform.position.x, transform.position.y, WHITE);
    }
  }
};
