#pragma once

#include <ECS/entity/entity.hpp>
#include <ECS/ECS.h>
#include <json_util.hpp>


struct EntitySerilization {
  void Serialize(const Entity& e, ECS& ecs, json& j) {}

  void Deserialization(Entity& e, ECS& ecs, const json& j) {
  } 
};
