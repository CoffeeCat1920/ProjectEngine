#include <ECS/tags/tagArray.hpp>
#include <core/setting.hpp>
#include <ECS/entity/entity.hpp>
#include <cassert>
#include <string>
#include <algorithm>

EntityManager::EntityManager() {
  for (int entity = 0; entity < (int)MAX_ENTITIES; entity++) {
    availableEntites.push(entity);
  } 
}

std::string EntityManager::GetName(Entity entity) {
  return entityToNames[entity];
}

const EntityVec EntityManager::GetEntities(std::string name) {
  return NameToEntities[name];
}

const EntityVec EntityManager::GetEntities() const {
  return livingEntites;
}

Entity EntityManager::CreateEntity(std::string name) {
  assert(LivingEntityCount < MAX_ENTITIES && "Too many Entities");
  
  Entity entity = availableEntites.front();
  entityToNames.insert({entity, name});
  availableEntites.pop();
  livingEntites.push_back(entity);
  LivingEntityCount++;

  return entity;
}

void EntityManager::EntityDestroyed(Entity entity) {
  assert(entity < MAX_ENTITIES && "Invalid Entity"); 

  availableEntites.push(entity);
  entityToNames.erase(entity);
  livingEntites.erase(
    std::remove(livingEntites.begin(), livingEntites.end(), entity),
    livingEntites.end()
  );
  --LivingEntityCount;

  return;
}
