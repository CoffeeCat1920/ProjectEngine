#pragma once

#include <ECS/component/component.hpp>
#include <ECS/entity/entity.hpp>
#include <ECS/system/system.hpp>
#include <memory>
#include <utility>

class ECS {
  
private:
  std::shared_ptr<EntityManager> entityManager;
  std::shared_ptr<ComponentManager> componentManager;
  std::shared_ptr<SystemManager> systemManager;
  
public:

  ECS() :
    entityManager(std::make_shared<EntityManager>()),
    componentManager(std::make_shared<ComponentManager>()),
    systemManager(std::make_shared<SystemManager>())
  {}

  Entity AddEntity(std::string name) {
    return entityManager->CreateEntity(name);
  }

  void RemoveEntity(Entity entity) {
    entityManager->EntityDestroyed(entity);
    componentManager->EntityDestroyed(entity); 
  }

  template<typename... Components>
  void RegisterComponent() {
    (componentManager->RegisterComponent<Components>(), ...);  
  } 
  
  template<typename... Components>
  void AddComponent(Entity entity, Components&&... components) {
    (componentManager->AddComponent(entity, std::forward<Components>(components)), ...);
  }

  template<typename ...Components>
  EntityVec GetEntities() {
    const EntityVec entities = entityManager->GetEntities();
    return componentManager->GetEntity<Components ...>(entities);
  }

  template<typename Component> 
  Component& GetComponent(Entity entity) {
    return componentManager->GetComponent<Component>(entity);
  }

  template<typename... Components> 
  void RemoveComponent(Entity entity) {
    (componentManager->RemoveComponent<Components>(entity), ...);
  }


  template<typename... System>
  void RegisterSystem() {
    (systemManager->RegisterSystem<System>(entityManager->GetEntities()), ...);   
  }

  template<typename... System>
  void RegisterSystem(EntityVec entities) {
    (systemManager->RegisterSystem<System>(entities), ...);   
  }

  template<typename System>
  std::shared_ptr<System> GetSystem() {
    return systemManager->GetSystem<System>();
  }
};
