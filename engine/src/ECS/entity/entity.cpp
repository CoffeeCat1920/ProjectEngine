#include "ECS/tags/tagArray.hpp"
#include "core/setting.hpp"
#include <ECS/entity/entity.hpp>
#include <cassert>

EntityManager::EntityManager() {
  for (int entity = 0; entity < (int)MAX_ENTITIES; entity++) {
    availableEntites.push(entity);
  } 
}

Entity EntityManager::CreateEntity() {
  assert(LivingEntityCount < MAX_ENTITIES && "Too many Entities");
  
  Entity entity = availableEntites.front();
  availableEntites.pop();
  LivingEntityCount++;

  return entity;
}

void EntityManager::DestroyEntity(Entity entity) {
  assert(entity < MAX_ENTITIES && "Invalid Entity"); 

  availableEntites.push(entity);
  entityToTags.erase(entity);
  --LivingEntityCount;

  return;
}

void EntityManager::AddTag(Entity entity, std::string tagname) {
  assert(entity < MAX_ENTITIES && "Invalid Entity");
  if (!tagArray.ValidTag(tagname)) {
    tagArray.AddTag(tagname);
  }
  
  entityToTags[entity].insert(tagArray.GetTag(tagname));
}
