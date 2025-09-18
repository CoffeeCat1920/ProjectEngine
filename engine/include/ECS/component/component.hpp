#pragma once
#include "ECS/entity/entity.hpp"
#include <ECS/componentArray/componentArray.hpp>
#include <cstdint>
#include <map>
#include <memory>
#include <typeinfo>
#include <unordered_map>

using ComponentId = uint64_t;

class ComponentManager {
private:
  std::unordered_map<const char*, ComponentId> componentIds{};
  std::map<ComponentId, std::unique_ptr<IComponentArray>> componentArrays; 
  ComponentId nextComponentId = 0;
  
  template<typename T>
  ComponentArray<T>* GetArray() {
    const char* typeName = typeid(T).name();
    assert(componentIds.find(typeName) != componentIds.end() && "Component not registered before use.");
    
    return static_cast<ComponentArray<T>*>(componentArrays[componentIds[typeName]].get());
  }

public:
  template<typename T>
  void RegisterComponent() {
    const char* name = typeid(T).name();
    assert(componentIds.find(name) == componentIds.end() && "Registering component type more than once.");
    
    componentIds[name] = nextComponentId;
    componentArrays[nextComponentId] = std::make_unique<ComponentArray<T>>();
    nextComponentId++;
  }
  
  template<typename T>
  void AddComponent(Entity entity, T component) {
    GetArray<T>()->InsertData(entity, std::move(component));
  }
  
  template<typename T>
  void RemoveComponent(Entity entity) {
    GetArray<T>()->RemoveData(entity);
  }
  
  template<typename T>
  T& GetComponent(Entity entity) {
    return GetArray<T>()->GetData(entity);
  }
  
  template<typename T>
  ComponentId GetComponentId() {
    const char* typeName = typeid(T).name();
    assert(componentIds.find(typeName) != componentIds.end() && "Component not registered before use.");
    return componentIds[typeName];
  }
};
