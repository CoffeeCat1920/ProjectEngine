#pragma once

#include "ComponentRegistry/ComponentRegistry.hpp"
#include "json.hpp"
#include <json_util.hpp>
#include <string>

struct CPlayerA {
  std::string dummy;
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CPlayerA, dummy);
};
REFLECTION(CPlayerA);

struct CPlayerB {
  std::string dummy;
  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CPlayerB, dummy);
};
REFLECTION(CPlayerB);
