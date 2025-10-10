#pragma once

#include <ECS/ECS.h>
#include <json_util.hpp>

template<typename T>
void SerializeComponent(Entity e, ECS& ecs, json& j) {}

template<typename T>
void DeserializationComponent(Entity& e, ECS& ecs, const json& j) {
  T component = j.get<T>();
  ecs.AddComponent(e, component);
}
