#pragma once

#include <ECS/entity/entity.hpp>
#include <ECS/ECS.h>
#include <json_util.hpp>

namespace EntitySerilizer {
  inline void Serialize(const Entity &e, ECS &ecs, json &j) {}
  inline void Deserialization(Entity &e, ECS &ecs, const json &j) {}
};
