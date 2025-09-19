#pragma once

#include <cstdint>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include <core/setting.hpp>
#include <core/setting.hpp>

using Entity = uint64_t;
using EntityVec = std::vector<Entity>;

class EntityManager {
  
private:
  std::queue<Entity> availableEntites{};

  std::unordered_map<Entity, std::string> entityToNames{};
  std::unordered_map<std::string, EntityVec> NameToEntities{}; 

  uint64_t LivingEntityCount = 0; 
  
public:
  EntityManager();

  Entity CreateEntity(std::string name);

  std::string GetName(Entity entity);
  EntityVec GetEntities(std::string);

  void EntityDestroyed(Entity);
};
