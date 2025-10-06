#pragma once

#include <raylib.h>
#include <json_util.hpp>

struct CRigidBody {
  Vector2 velocity{};
  Vector2 acceleration{};
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CRigidBody, velocity, acceleration)
};
