#pragma once

#include "ComponentRegistry/ComponentRegistry.hpp"
#include "json.hpp"
#include <json_util.hpp>
#include <raylib.h>

struct CTransform {
  Vector2 position{0, 0};
  Vector2 scale{1, 1};
  float rotation = 0.0f;
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CTransform, position, scale)
};
REFLECTION(CTransform);

struct CRectangle {
  float w = 12.0f, h = 12.0f;
  CRectangle() = default;
  CRectangle(float w, float h) : w(w), h(h) {}
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CRectangle, w, h);
};
REFLECTION(CRectangle);

struct CTriangle {
  float side = 12.0f;
  CTriangle() = default;
  CTriangle(float side) : side(side) {}
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CTriangle, side);
};
REFLECTION(CTriangle);

struct CIsoTriangle {
  float base = 12.0f, height = 12.0f;
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CIsoTriangle, base, height);
};
REFLECTION(CIsoTriangle);

struct CSprite {
  std::filesystem::path path = "";
  Texture2D texture;
  CSprite(std::filesystem::path p) : path(std::move(p)) {}
  CSprite() { path = "./assets/bird.png"; }
};

inline void to_json(json &j, const CSprite &s) {
  j = json{{"path", s.path.string()}};
}

inline void from_json(const json &j, CSprite &s) {
  s.path = j.at("path").get<std::string>();
}
REFLECTION(CSprite);
