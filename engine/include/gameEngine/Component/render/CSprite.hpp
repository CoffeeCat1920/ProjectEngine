#pragma once

#include <raylib.h>
#include <json_util.hpp>

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

}; 

inline void to_json(json& j, const CSprite& s) {
  j = json{ {"path", s.path.string()} };
}

inline void from_json(const json& j, CSprite& s) {
  s.path = j.at("path").get<std::string>();
  s.texture = LoadTexture(s.path.c_str());
}
