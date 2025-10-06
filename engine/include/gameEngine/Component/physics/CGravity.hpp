#pragma once

#include <raylib.h>
#include <json_util.hpp>

struct CGravity {
  Vector2 force{};
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CGravity, force)
};
