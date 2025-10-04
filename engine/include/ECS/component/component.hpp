#pragma once

#include <core/setting.hpp>
#include <ECS/entity/entity.hpp>
#include <ECS/componentArray/componentArray.hpp>
#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <typeinfo>
#include <unordered_map>

using ComponentId = uint64_t;
using Signature = std::bitset<MAX_COMPONENTS>;

class ComponentManager {
  
private:
  std::map<ComponentId, std::unique_ptr<IComponentArray>> componentArrays{}; 
  std::unordered_map<std::string, ComponentId> componentIds{};
  ComponentId nextComponentId = 0;

  std::array<Signature, MAX_ENTITIES> entitySignatures{};
  std::unordered_map<Signature, EntitySet> archetypes{};

  template<typename T>
  ComponentArray<T>* GetArray() {
    const char* typeName = typeid(T).name();
    assert(componentIds.find(typeName) != componentIds.end() && "Component not registered before use.");
    return static_cast<ComponentArray<T>*>(componentArrays[componentIds[typeName]].get());
  }

  template<typename ...T>
  Signature GetSignature() {
    Signature signature;
    ((signature.set(GetComponentId<T>())), ...);
    return signature;
  }

  bool IsFull(Entity entity) {
    return entitySignatures.at(entity).all();
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
  
  template<typename ComponentName>
  void AddComponent(Entity entity, ComponentName component) {
    assert(!IsFull(entity) && "Can't register components more than max count");
    GetArray<ComponentName>()->InsertData(entity, component);
    ComponentId componentId = GetComponentId<ComponentName>();
    archetypes[entitySignatures.at(entity)].erase(entity);
    entitySignatures.at(entity).set(componentId);
    archetypes[entitySignatures.at(entity)].insert(entity); 
  }

  template<typename T>
  void RemoveComponent(Entity entity) {
    GetArray<T>()->RemoveData(entity);
    ComponentId componentId = GetComponentId<T>();
    archetypes[entitySignatures.at(entity)].erase(entity);
    entitySignatures.at(entity).reset(componentId);
    archetypes[entitySignatures.at(entity)].insert(entity);
  }

  template<typename T>
  bool HasComponent(Entity entity) {
    ComponentId componentId = GetComponentId<T>();     
    return entitySignatures.at(entity).test(componentId);
  }
  
  template<typename T>
  T& GetComponent (Entity entity) {
    return GetArray<T>()->GetData(entity);
  }

  template<typename T>
  ComponentId GetComponentType() {
    const char* name = typeid(T).name();
    const auto& it = componentIds.find(name); 
    assert(it != componentIds.end() && "Component is unregistered");
    return it->second; 
  }
  
  template<typename T>
  ComponentId GetComponentId() {
    const char* typeName = typeid(T).name();
    assert(componentIds.find(typeName) != componentIds.end() && "Component not registered before use.");
    return componentIds[typeName];
  }

	void EntityDestroyed(Entity entity) {
		for (auto const& pair : componentArrays) {
			auto const& component = pair.second;
			component->EntityDestroyed(entity);
      archetypes[entitySignatures.at(entity)].erase(entity);
		}
	}

  const EntitySet& GetArchetypeEntities(const Signature& signature) const {
    static const EntitySet empty;
    auto it = archetypes.find(signature);
    return (it != archetypes.end()) ? it->second : empty;
  }

  Signature GetSignature(Entity entity) {
    return entitySignatures[entity];
  }

  void SetSignature(Entity entity, Signature signature) {
    entitySignatures[entity] = signature;
  }
};
