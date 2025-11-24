#pragma once

#include "../components/components.hpp"
#include <ComponentRegistry/render/Render.hpp>
#include <ECS/system/system.hpp>
#include <SystemRegistry/SystemRegistry.hpp>
#include <cmath>
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

  inline Vector2 GetTopDirectionWorld(CTransform &t) {
    Vector2 localDir = {0.0f, -1.0f};

    float rad = t.rotation * DEG2RAD;

    float s = sinf(rad);
    float c = cosf(rad);

    Vector2 worldDir;
    worldDir.x = localDir.x * c - localDir.y * s;
    worldDir.y = localDir.x * s + localDir.y * c;

    return worldDir;
  }

  inline void ApplyMovement(CTransform &t, Vector2 dir, float speed) {
    t.position.x += dir.x * speed;
    t.position.y += dir.y * speed;
  }

  void Update() override {
    if (!IsKeyDown(KEY_UP))
      return;

    const float moveSpeed = 5.0f;

    for (auto &entity : System::entities) {
      auto &t = gEcs.GetComponent<CTransform>(entity);

      Vector2 dir = GetTopDirectionWorld(t);
      ApplyMovement(t, dir, moveSpeed);
    }
  }
};
REGISTER_SYSTEM(SMoveTowardsTop, Physics, CIsoTriangle, CTransform);

struct SScreenWrap : System {
  ECS &gEcs = ECS::Instance();

  void Update() override {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    for (auto &entity : System::entities) {
      auto &transform = gEcs.GetComponent<CTransform>(entity);

      if (transform.position.x < 0) {
        transform.position.x = screenWidth;
      } else if (transform.position.x > screenWidth) {
        transform.position.x = 0;
      }

      if (transform.position.y < 0) {
        transform.position.y = screenHeight;
      } else if (transform.position.y > screenHeight) {
        transform.position.y = 0;
      }
    }
  }
};
REGISTER_SYSTEM(SScreenWrap, Physics, CIsoTriangle, CTransform);

struct SPlayerShooting : System {
  ECS &gEcs = ECS::Instance();
  float shootCooldown = 0.0f;
  const float shootDelay = 0.25f; // seconds between shots

  inline Vector2 GetTopDirectionWorld(CTransform &t) {
    Vector2 localDir = {0.0f, -1.0f};
    float rad = t.rotation * DEG2RAD;
    float s = sinf(rad);
    float c = cosf(rad);
    Vector2 worldDir;
    worldDir.x = localDir.x * c - localDir.y * s;
    worldDir.y = localDir.x * s + localDir.y * c;
    return worldDir;
  }

  void Update() override {
    float dt = GetFrameTime();
    shootCooldown -= dt;

    if (IsKeyPressed(KEY_SPACE) && shootCooldown <= 0.0f) {
      for (auto &entity : System::entities) {
        auto &transform = gEcs.GetComponent<CTransform>(entity);
        Vector2 shootDir = GetTopDirectionWorld(transform);

        // Create projectile entity
        const float projectileSpeed = 10.0f;
        Entity projectile = gEcs.AddEntity("Projectile");
        gEcs.AddComponent(
            projectile,
            CTransform{
                .position = transform.position,
                .scale = {0.3f, 0.3f},
                .rotation = transform.rotation,
            },
            CIsoTriangle{.base = 10, .height = 12},
            CProjectile{.velocity = {shootDir.x * projectileSpeed,
                                     shootDir.y * projectileSpeed}});

        shootCooldown = shootDelay;
      }
    }
  }
};
REGISTER_SYSTEM(SPlayerShooting, Physics, CIsoTriangle, CTransform);

struct SProjectileMovement : System {
  ECS &gEcs = ECS::Instance();

  void Update() override {
    float dt = GetFrameTime();

    for (auto &entity : System::entities) {
      auto &transform = gEcs.GetComponent<CTransform>(entity);
      auto &projectile = gEcs.GetComponent<CProjectile>(entity);

      // Move projectile
      transform.position.x += projectile.velocity.x * dt * 60.0f;
      transform.position.y += projectile.velocity.y * dt * 60.0f;

      // Update lifetime
      projectile.lifetime -= dt;
      if (projectile.lifetime <= 0.0f) {
        gEcs.RemoveEntity(entity);
      }
    }
  }
};
REGISTER_SYSTEM(SProjectileMovement, Physics, CProjectile, CTransform);
