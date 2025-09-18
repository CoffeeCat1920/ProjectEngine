#pragma once

#include <core/setting.hpp>
#include <ECS/entity/entity.hpp>
#include <array>
#include <cassert>
#include <cstddef>
#include <unordered_map>

class IComponentArray {
public: 
  virtual ~IComponentArray() = default;
  virtual void EntityDestroyed(Entity entity) = 0;
};


template<typename T>
class ComponentArray : public IComponentArray {
private:
  std::array<T, MAX_ENTITIES> componentArray;  
  std::unordered_map<Entity, size_t> entityToIndex;
  std::unordered_map<size_t, Entity> indexToEntity;
  size_t size = 0;
  
public:
  ComponentArray() = default;
  
  void InsertData(Entity entity, T component) {
    assert(entityToIndex.find(entity) == entityToIndex.end() && "Component added to same entity more than once.");
    size_t newIndex = size;
    entityToIndex[entity] = newIndex;
    indexToEntity[newIndex] = entity;
    componentArray[newIndex] = std::move(component);
    ++size;
  }
  
  void RemoveData(Entity entity) {
    assert(entityToIndex.find(entity) != entityToIndex.end() && "Component is not added to entity.");
    
    size_t indexOfRemovedEntity = entityToIndex[entity];
    size_t indexOfLastEntity = size - 1;
    componentArray[indexOfRemovedEntity] = componentArray[indexOfLastEntity];

    Entity entityOfLastElement = indexToEntity[indexOfLastEntity];
    entityToIndex[entityOfLastElement] = indexOfRemovedEntity;
    indexToEntity[indexOfRemovedEntity] = entityOfLastElement;

    entityToIndex.erase(entity);
    indexToEntity.erase(indexOfLastEntity);

    --size;
  }
  
  T& GetData(Entity entity) {
    assert(entityToIndex.find(entity) != entityToIndex.end() && "Retrieving non-existent component.");
    return componentArray[entityToIndex[entity]];
  }
  
  void EntityDestroyed(Entity entity) override {
    if (entityToIndex.find(entity) != entityToIndex.end()) {
      RemoveData(entity);
    }
  }
};
