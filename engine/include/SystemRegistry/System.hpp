#pragma once

#include "ComponentRegistry/physics/Physics.hpp"
#include "ComponentRegistry/render/Render.hpp"
#include "ECS/system/system.hpp"
#include <ComponentRegistry/Component.hpp>
#include <ECS/ECS.h>
#include <ECS/utils/signatures.hpp>
#include <SystemRegistry/SystemRegistry.hpp>
#include <core/colors.hpp>
#include <raylib.h>

struct SPhysics : System {
  ECS &gEcs = ECS::Instance();
  void Update() override {
    for (const auto &entity : System::entities) {
      auto &rigidBody = gEcs.GetComponent<CRigidBody>(entity);
      auto &transform = gEcs.GetComponent<CTransform>(entity);
      auto const &gravity = gEcs.GetComponent<CGravity>(entity);

      transform.position.x += rigidBody.velocity.x;
      transform.position.y += rigidBody.velocity.y;

      rigidBody.velocity.x += gravity.force.x;
      rigidBody.velocity.y += gravity.force.y;
    }
  }
};
REGISTER_SYSTEM(SPhysics, Physics, CGravity, CRigidBody, CTransform);

struct SRender : System {
  ECS &gEcs = ECS::Instance();
  void Update() override {
    for (const auto &entity : System::entities) {
      auto &rectangle = gEcs.GetComponent<CRectangle>(entity);
      auto &transform = gEcs.GetComponent<CTransform>(entity);
      DrawRectangle(transform.position.x, transform.position.y, rectangle.w,
                    rectangle.h, GRUVBOX_RED);
    }
  }
};
REGISTER_SYSTEM(SRender, Render, CRectangle, CTransform);
