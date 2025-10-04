#pragma once

#include <ECS/ECS.h>
#include <ECS/entity/entity.hpp>
#include <json_util.hpp>

struct IComponentSerializer {
  virtual void Serialize(Entity e, ECS& ecs, json& j) = 0;
  virtual void Deserialization(Entity e, ECS& ecs, json j) = 0;
};

template<typename T>
struct ComponentSerializer : IComponentSerializer {
  void Serialize(Entity e, ECS& ecs, json& j) override {
    if (ecs.HasComponent<T>(e)) {
      const auto& t = ecs.GetComponent<T>(e); 
      j[typeid(t).name()] = t;
    }
  }
};
