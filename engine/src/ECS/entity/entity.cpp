#include <ECS/tags/tagArray.hpp>
#include <core/setting.hpp>
#include <ECS/entity/entity.hpp>
#include <cassert>
#include <string>

EntityManager::EntityManager() {
  for (int entity = 0; entity < (int)MAX_ENTITIES; entity++) {
    availableEntites.push(entity);
  } 
}

std::string EntityManager::GetName(Entity entity) {
  return entityToNames[entity];
}

const EntitySet EntityManager::GetEntities(std::string name) {
  return NameToEntities[name];
}

const EntitySet EntityManager::GetEntities() const {
  return livingEntites;
}

Entity EntityManager::CreateEntity(std::string name) {
  assert(LivingEntityCount < MAX_ENTITIES && "Too many Entities");
  
  Entity entity = availableEntites.front();
  entityToNames.insert({entity, name});
  availableEntites.pop();
  livingEntites.insert(entity);
  LivingEntityCount++;

  return entity;
}

void EntityManager::EntityDestroyed(Entity entity) {
  assert(entity < MAX_ENTITIES && "Invalid Entity"); 

  availableEntites.push(entity);
  entityToNames.erase(entity);
  livingEntites.erase(entity);
  --LivingEntityCount;

  return;
}
