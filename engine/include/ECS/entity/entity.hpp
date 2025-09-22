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
  std::unordered_map<std::string, EntitySet> NameToEntities{}; 

  EntitySet livingEntites{};

  uint64_t LivingEntityCount = 0; 
  
public:
  EntityManager();

  Entity CreateEntity(std::string name);

  std::string GetName(Entity entity);
  const EntitySet GetEntities(std::string);
  const EntitySet GetEntities() const; 

  void EntityDestroyed(Entity);
};
