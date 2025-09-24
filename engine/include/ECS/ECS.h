#pragma once

#include <ECS/component/component.hpp>
#include <ECS/entity/entity.hpp>
#include <ECS/system/system.hpp>
#include <iostream>
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
    systemManager->EntityDestroyed(entity);
  }

  template<typename Components>
  void RegisterComponent() {
    componentManager->RegisterComponent<Components>();  
  } 
 
  template<typename Component>
  void AddComponent(Entity entity, Component component) {
    componentManager->AddComponent<Component>(entity, component);

    Signature signature = componentManager->GetSignature(entity); 
    systemManager->EntitySignatureChanged(entity, signature);
  }

  template<typename... Components>
  void AddComponent(Entity entity, Components... components) {
    (componentManager->AddComponent(entity, std::forward<Components>(components)), ...);

    const Signature signature = componentManager->GetSignature(entity);
    systemManager->EntitySignatureChanged(entity, signature);
  }

  template<typename... Components>
  void RemoveComponents(Entity entity) {
    (componentManager->RemoveComponent<Components>(entity), ...);
    const Signature signature = componentManager->GetSignature(entity); 
    systemManager->EntitySignatureChanged(entity, signature);
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

  template<typename Component>
  ComponentId GetComponentId() {
    return componentManager->GetComponentType<Component>();
  }

  template<typename... Components> 
  void RemoveComponent(Entity entity) {
    (componentManager->RemoveComponent<Components>(entity), ...);
  }


  template<typename System>
  std::shared_ptr<System> RegisterSystem() {
    return systemManager->RegisterSystem<System>();   
  }

  template<typename System>
  void SetSystemSignature(Signature signature) {
    systemManager->SetSignature<System>(signature);
  }

};
