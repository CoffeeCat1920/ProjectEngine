#pragma once
#include <gameEngine/Component/ComponentRegistry.hpp>
#include <filesystem>
#include <raylib.h>
#include <json.hpp>


inline void to_json(json& j, const Vector2& v) {
  j = json{ 
    {"x", v.x}, 
    {"y", v.y} 
  };
}

inline void from_json(const json& j, Vector2& v) {
  v.x = j.at("x").get<float>();
  v.y = j.at("y").get<float>();
}

struct CGravity {
  Vector2 force{};
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CGravity, force)
};

struct CTransform {
  Vector2 position{};
  Vector2 scale{};
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CTransform, position, scale)
};

struct CRigidBody {
  Vector2 velocity{};
  Vector2 acceleration{};
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CRigidBody, velocity, acceleration)
};

struct CRectangle {
  Rectangle rectangle{0, 0, 16, 16};
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CRectangle, rectangle)
};

struct CSprite {
  std::filesystem::path path = "";
  Texture2D texture;

  CSprite(std::filesystem::path p) : path(std::move(p)) {
    texture = LoadTexture(path.c_str());
  }

  CSprite() {
    path = "./assets/bird.png";
    texture = LoadTexture(path.c_str());
  }

  ~CSprite() {
    UnloadTexture(texture);
  }
};

inline void to_json(json& j, const CSprite& s) {
  j = json{ {"path", s.path.string()} };
}

inline void from_json(const json& j, CSprite& s) {
  s.path = j.at("path").get<std::string>();
  s.texture = LoadTexture(s.path.c_str());
}
