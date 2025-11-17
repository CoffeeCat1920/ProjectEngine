#pragma once

#include "../components/components.hpp"
#include "core/colors.hpp"
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

struct STriangle : System {
  ECS &gEcs = ECS::Instance();

  inline void GetTriangleVerts(float side, Vector2 &a, Vector2 &b, Vector2 &c) {
    float h = side * sqrtf(3.0f) / 2.0f;
    a = {0.0f, -h * 2.0f / 3.0f};
    b = {-side * 0.5f, h / 3.0f};
    c = {side * 0.5f, h / 3.0f};
  }

  inline Vector2 Rotate(Vector2 v, float deg) {
    float r = deg * (PI / 180.0f);
    float cs = cosf(r);
    float sn = sinf(r);
    return {v.x * cs - v.y * sn, v.x * sn + v.y * cs};
  }

  void Update() override {
    for (const auto &entity : System::entities) {
      auto &tri = gEcs.GetComponent<CTriangle>(entity);
      auto &t = gEcs.GetComponent<CTransform>(entity);

      Vector2 a, b, c;
      GetTriangleVerts(tri.side, a, b, c);

      a.x *= t.scale.x;
      a.y *= t.scale.y;
      b.x *= t.scale.x;
      b.y *= t.scale.y;
      c.x *= t.scale.x;
      c.y *= t.scale.y;

      a = Rotate(a, t.rotation);
      b = Rotate(b, t.rotation);
      c = Rotate(c, t.rotation);

      a.x += t.position.x;
      a.y += t.position.y;
      b.x += t.position.x;
      b.y += t.position.y;
      c.x += t.position.x;
      c.y += t.position.y;

      DrawTriangle(a, b, c, GRUVBOX_AQUA);
    }
  }
};
REGISTER_SYSTEM(STriangle, Render, CTriangle, CTransform);

struct SDrawPlayer : System {
  ECS &gEcs = ECS::Instance();

  struct Points {
    Vector2 A{}, B{}, C{};
  };

  Points GetPoints(float base, float height, Vector2 origin) {
    Points points;
    points.A = Vector2{origin.x - (height / 2), origin.y - (base / 2)};
    points.B = Vector2{origin.x - (height / 2), origin.y + (base / 2)};
    points.C = Vector2{origin.x, origin.y + height / 2};
    return points;
  }

  void Update() override {
    for (const auto &entity : entities) {
      auto &player = gEcs.GetComponent<CPlayer>(entity);
      auto &transform = gEcs.GetComponent<CTransform>(entity);

      Vector2 origin = transform.position;

      Points p = GetPoints(player.base, player.height, origin);

      DrawTriangle(p.A, p.B, p.C, RED);
    }
  }
};
REGISTER_SYSTEM(SDrawPlayer, Render, CPlayer, CTransform);
