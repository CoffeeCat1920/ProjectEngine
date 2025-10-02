#pragma once
#include <filesystem>
#include <raylib.h>

struct CGravity {
  Vector2 force{};
};

struct CRigidBody {
  Vector2 velocity{};
  Vector2 acceleration{};
};

struct CTransform {
  Vector2 position{};
  Vector2 scale{};
};

struct CSprite {
  std::filesystem::path path = "";
  Texture2D texture = LoadTexture(path.c_str());
  CSprite(std::filesystem::path path) :
    path(path)
  {
    texture = LoadTexture(path.c_str());
  }
  CSprite() {
    path = "./assets/bird.png";
    texture = LoadTexture(path.c_str());
  }
};
