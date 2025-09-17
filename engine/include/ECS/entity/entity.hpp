#pragma once

#include "ECS/tags/tagArray.hpp"
#include <cstdint>
#include <core/setting.hpp>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using Entity = uint64_t;

class EntityManager {
  
private:
  std::queue<Entity> availableEntites{};
  std::unordered_map<Entity, std::unordered_set<Tag>> entityToTags{};
  TagArray tagArray{};

  uint64_t LivingEntityCount = 0; 
  
public:
  EntityManager();

  Entity CreateEntity();
  void AddTag(Entity, std::string); 
  void RemoveTag(Entity, std::string);
  void DestroyEntity(Entity);
};
