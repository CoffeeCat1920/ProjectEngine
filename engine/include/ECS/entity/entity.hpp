#pragma once

#include <cstdint>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include <core/setting.hpp>
#include <core/setting.hpp>

using Entity = uint64_t;
using EntityVec = std::vector<Entity>;
using EntitySet = std::set<Entity>;

class EntityManager {
  
private:
  std::queue<Entity> availableEntites{};

  std::unordered_map<Entity, std::string> entityToNames{};
  std::unordered_map<std::string, EntityVec> NameToEntities{}; 

  EntityVec livingEntites{};

  uint64_t LivingEntityCount = 0; 
  
public:
  EntityManager();

  Entity CreateEntity(std::string name);

  std::string GetName(Entity entity);
  const EntityVec GetEntities(std::string);
  const EntityVec GetEntities() const; 

  void EntityDestroyed(Entity);
};
