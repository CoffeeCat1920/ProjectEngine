#pragma once

#include <gameEngine/Component/ComponentRegistry.hpp>
#include "serialization/Component/Component.hpp"
#include <ECS/entity/entity.hpp>
#include <ECS/ECS.h>
#include <json_util.hpp>
#include <typeindex>



struct EntitySerilizer {

  void Serialize(const Entity &e, ECS &ecs, json &j) {}

  void Deserialization(Entity &e, ECS &ecs, const json &j) {
    for (const auto& [compName, compData] : j.items()) {
      std::type_index type = registry.Get(compName); 
      Deserialization<type>(e, ecs, compData);  
    }
  }

private:

  ComponentRegistry registry;
};
