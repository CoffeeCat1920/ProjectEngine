#pragma once

#include <ECS/component/component.hpp>
#include <ECS/entity/entity.hpp>
#include <memory>
#include <utility>

class ECS {
  
private:
  std::shared_ptr<EntityManager> entityManager;
  std::shared_ptr<ComponentManager> componentManager;
  
public:

  ECS() :
    entityManager(std::make_shared<EntityManager>()),
    componentManager(std::make_shared<ComponentManager>())
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

  template<typename Component> 
  Component& GetComponent(Entity entity) {
    return componentManager->GetComponent<Component>(entity);
  }

  template<typename... Components> 
  void RemoveComponent(Entity entity) {
    (componentManager->RemoveComponent<Components>(entity), ...);
  }
};
