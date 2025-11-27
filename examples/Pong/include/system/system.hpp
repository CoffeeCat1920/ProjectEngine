#pragma once

#include "../components/components.hpp"
#include "gameEngine/gameEngine.hpp"
#include <ComponentRegistry/render/Render.hpp>
#include <ECS/system/system.hpp>
#include <SystemRegistry/SystemRegistry.hpp>
#include <iostream>
#include <raylib.h>

struct SPlayerAInput : System {
  ECS &gEcs = ECS::Instance();
  void Update() override {
    for (auto &entity : System::entities) {
      auto &transform = gEcs.GetComponent<CTransform>(entity);

      if (IsKeyDown(KEY_UP)) {
        transform.position.y -= 5.0f;
      } else if (IsKeyDown(KEY_DOWN)) {
        transform.position.y += 5.0f;
      }
    }
  }
};
REGISTER_SYSTEM(SPlayerAInput, Physics, CRectangle, CTransform, CPlayerA);

struct SPlayerBInput : System {
  ECS &gEcs = ECS::Instance();
  void Update() override {
    for (auto &entity : System::entities) {
      auto &transform = gEcs.GetComponent<CTransform>(entity);

      if (transform.position.y < GetRenderHeight())
        std::cout << "Hello";

      if (IsKeyDown(KEY_W)) {
        transform.position.y -= 5.0f;
      } else if (IsKeyDown(KEY_S)) {
        transform.position.y += 5.0f;
      }
    }
  }
};
REGISTER_SYSTEM(SPlayerBInput, Physics, CRectangle, CTransform, CPlayerB);
