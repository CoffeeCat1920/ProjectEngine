#pragma once

#include "ComponentRegistry/ComponentRegistry.hpp"
#include "json.hpp"

struct CPlayer {
  float base = 12.0f, height = 12.0f;
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CPlayer, base, height);
};
REFLECTION(CPlayer);
