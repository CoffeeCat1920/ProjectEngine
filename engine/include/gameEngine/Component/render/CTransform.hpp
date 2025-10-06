#pragma once

#include <raylib.h>
#include <json_util.hpp>

struct CTransform {
  Vector2 position{};
  Vector2 scale{};
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CTransform, position, scale)
};
