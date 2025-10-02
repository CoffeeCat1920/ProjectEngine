#pragma once
#include <filesystem>
#include <raylib.h>

struct CGravity {
  Vector2 force{};
};

struct CTransform {
  Vector2 position{};
  Vector2 scale{};
};

struct CRigidBody {
  Vector2 velocity{};
  Vector2 acceleration{};
};


struct CRectangle {
  Rectangle rectangle{0, 0, 16, 16};
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
