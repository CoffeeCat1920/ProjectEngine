#pragma once

#include <ComponentRegistry/render/Render.hpp>
#include <ECS/system/system.hpp>
#include <SystemRegistry/SystemRegistry.hpp>
#include <cmath>
#include <raylib.h>

struct SPlayerInput : System {
  ECS &gEcs = ECS::Instance();
  void Update() override {
    for (auto &entity : System::entities) {
      // auto &triangle = gEcs.GetComponent<CTriangle>(entity);
      auto &transform = gEcs.GetComponent<CTransform>(entity);

      if (IsKeyDown(KEY_LEFT)) {
        transform.rotation -= 5.0f;
      } else if (IsKeyDown(KEY_RIGHT)) {
        transform.rotation += 5.0f;
      }
    }
  }
};
REGISTER_SYSTEM(SPlayerInput, Render, CTriangle, CTransform);

struct SMoveTowardsTop : System {
  ECS &gEcs = ECS::Instance();

  inline Vector2 GetLocalTopPoint(float side) {
    float h = side * sqrtf(3.0f) / 2.0f;
    return {0.0f, h / 3.0f};
  }

  inline Vector2 Rotate(Vector2 v, float deg) {
    float r = deg * (PI / 180.0f);
    float cs = cosf(r);
    float sn = sinf(r);
    return {v.x * cs - v.y * sn, v.x * sn + v.y * cs};
  }

  inline Vector2 Normalize(Vector2 v) {
    float len = sqrtf(v.x * v.x + v.y * v.y);
    if (len <= 0.0001f)
      return {0, 0};
    return {v.x / len, v.y / len};
  }

  inline Vector2 GetTopDirectionWorld(CTriangle &tri, CTransform &t) {
    Vector2 localTop = GetLocalTopPoint(tri.side);

    localTop.x *= t.scale.x;
    localTop.y *= t.scale.y;

    Vector2 rotated = Rotate(localTop, t.rotation);

    return Normalize(rotated);
  }

  inline void ApplyMovement(CTransform &t, Vector2 dir, float speed) {
    t.position.x += dir.x * speed;
    t.position.y += dir.y * speed;
  }

  void Update() override {
    if (!IsKeyDown(KEY_SPACE))
      return;

    const float moveSpeed = -2.0f;

    for (auto &entity : System::entities) {
      auto &tri = gEcs.GetComponent<CTriangle>(entity);
      auto &t = gEcs.GetComponent<CTransform>(entity);

      Vector2 dir = GetTopDirectionWorld(tri, t);
      ApplyMovement(t, dir, moveSpeed);
    }
  }
};
REGISTER_SYSTEM(SMoveTowardsTop, Physics, CTriangle, CTransform);
