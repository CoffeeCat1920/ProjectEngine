#pragma once

#include <ComponentRegistry/render/Render.hpp>
#include <ECS/system/system.hpp>
#include <SystemRegistry/SystemRegistry.hpp>
#include <raylib.h>

struct SPlayerInput : System {
  ECS &gEcs = ECS::Instance();
  void Update() override {
    for (auto &entity : System::entities) {
      auto &transform = gEcs.GetComponent<CTransform>(entity);

      if (IsKeyDown(KEY_LEFT)) {
        transform.rotation -= 5.0f;
      } else if (IsKeyDown(KEY_RIGHT)) {
        transform.rotation += 5.0f;
      }
    }
  }
};
REGISTER_SYSTEM(SPlayerInput, Render, CIsoTriangle, CTransform);
