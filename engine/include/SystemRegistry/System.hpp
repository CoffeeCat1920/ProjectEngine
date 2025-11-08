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

struct SRectangle : System {
  ECS &gEcs = ECS::Instance();
  void Update() override {
    for (const auto &entity : System::entities) {
      auto &rectangle = gEcs.GetComponent<CRectangle>(entity);
      auto &transform = gEcs.GetComponent<CTransform>(entity);
      DrawRectangle(transform.position.x, transform.position.y, rectangle.w,
                    rectangle.h, RED);
    }
  }
};
REGISTER_SYSTEM(SRectangle, Render, CRectangle, CTransform);

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

      DrawTriangle(a, b, c, GRUVBOX_LIGHT0);
    }
  }
};
REGISTER_SYSTEM(STriangle, Render, CTriangle, CTransform);
