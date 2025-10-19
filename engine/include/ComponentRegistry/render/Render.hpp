#pragma once

#include "ComponentRegistry/ComponentRegistry.hpp"
#include "json.hpp"
#include <json_util.hpp>
#include <raylib.h>

struct CTransform {
  Vector2 position{0, 0};
  Vector2 scale{1, 1};
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CTransform, position, scale)
};
REFLECTION(CTransform);

struct CRectangle {
  float w = 12, h = 12;
  CRectangle() = default;
  CRectangle(float w, float h) : w(w), h(h) {}
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CRectangle, w, h);
};
REFLECTION(CRectangle);

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
