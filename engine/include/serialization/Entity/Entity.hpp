#pragma once

#include "serialization/Component/Component.hpp"
#include <ECS/entity/entity.hpp>
#include <ECS/ECS.h>
#include <json_util.hpp>
#include <typeindex>

struct EntitySerilizer {

  void Serialize(const Entity &e, ECS &ecs, json &j) {}

  void Deserialization(Entity &e, ECS &ecs, const json &j) {
    for (const auto& [compName, compData] : j.items()) {
    }
  }

private:

};
