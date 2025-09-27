#pragma once

#include <ECS/entity/entity.hpp>
#include <set>

struct System {
  std::set<Entity> entities;
};
