#pragma once

#include <raylib.h>
#include <core/colors.hpp>
#include <ComponentRegistry/Component.hpp>
#include <ECS/ECS.h>
#include <ECS/utils/signatures.hpp>
#include <SystemRegistry/SystemRegistry.hpp>

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
SYSTEM_PHYSICS_REGISTERATION(SPhysics);

struct SRender : System {
  ECS& gEcs = ECS::Instance();
  void Update() {
    for (const auto& entity : System::entities) {
      auto& rectangle = gEcs.GetComponent<CRectangle>(entity);
      auto& transform = gEcs.GetComponent<CTransform>(entity);
      DrawRectangle(transform.position.x, transform.position.y, rectangle.w , rectangle.h, GRUVBOX_RED);
    }
  }
};
SYSTEM_RENDER_REGISTERATION(SRender); 
