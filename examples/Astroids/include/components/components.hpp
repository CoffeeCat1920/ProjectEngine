#pragma once

#include "ComponentRegistry/ComponentRegistry.hpp"
#include "json.hpp"
#include "json_util.hpp"
#include "raylib.h"

struct CProjectile {
  Vector2 velocity;
  float lifetime = 2.0f;
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CProjectile, velocity, lifetime);
};
REFLECTION(CProjectile);
