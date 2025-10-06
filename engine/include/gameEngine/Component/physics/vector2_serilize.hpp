#pragma once

#include <raylib.h>
#include <json_util.hpp>

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
