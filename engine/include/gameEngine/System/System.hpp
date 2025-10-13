#pragma once

#include "core/colors.hpp"
#include "gameEngine/Component/render/Render.hpp"
#include "raylib.h"
#include <ECS/ECS.h>
#include <ECS/utils/signatures.hpp>
#include <gameEngine/Component/Component.hpp>

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
      auto& rectangle = gEcs.GetComponent<CRectangle>(entity);
      auto& transform = gEcs.GetComponent<CTransform>(entity);
      DrawRectangle(transform.position.x, transform.position.y, rectangle.w * transform.scale.x, rectangle.h * transform.scale.y, GRUVBOX_RED);
    }
  }
};
