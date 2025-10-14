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

  explicit ECS() :
    entityManager(std::make_shared<EntityManager>()),
    componentManager(std::make_shared<ComponentManager>()),
    systemManager(std::make_shared<SystemManager>())
  {}

public:

  ECS(const ECS&) = delete;
  ECS& operator=(const ECS&) = delete;
  ECS(ECS&&) = delete;
  ECS& operator=(ECS&&) = delete;

  static ECS& Instance() {
    static ECS instance;  
    return instance;      
  }

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

  template<typename... ComponentsNames>
  void AddComponent(Entity entity, ComponentsNames... components) {
    (componentManager->AddComponent(entity, std::forward<ComponentsNames>(components)), ...);

    const Signature signature = componentManager->GetSignature(entity);
    systemManager->EntitySignatureChanged(entity, signature);
  }

  template<typename... Components>
  void RemoveComponents(Entity entity) {
    (componentManager->RemoveComponent<Components>(entity), ...);
    const Signature signature = componentManager->GetSignature(entity); 
    systemManager->EntitySignatureChanged(entity, signature);
  }

  template<typename Component>
  bool HasComponent(Entity entity) {
    return componentManager->HasComponent<Component>(entity);
  }

  template<typename Component> 
  Component& GetComponent(Entity entity) {
    return componentManager->GetComponent<Component>(entity);
  }

  template<typename Component>
  ComponentId GetComponentId() {
    return componentManager->GetComponentId<Component>();
  }

  template<typename... Components> 
  void RemoveComponent(Entity entity) {
    (componentManager->RemoveComponent<Components>(entity), ...);
  }


  template<typename System>
  void SetSystemSignature(Signature signature) {
    systemManager->SetSignature<System>(signature);
  }

  template<typename System>
  void SetSystemSignature(ComponentId componentId) {
    systemManager->SetSignature<System>(componentId);
  }

  template<typename System, typename... Components>
  void SetSystemSignature() {
    systemManager->SetSignature<System>({
      GetComponentId<Components>()... // expand into a list
    });
  }

  template<typename System>
  std::shared_ptr<System> RegisterSystem() {
    return systemManager->RegisterSystem<System>();   
  }

  template<typename System, typename... Components>
  std::shared_ptr<System> RegisterSystemWithSignatures() {
    const auto& system = systemManager->RegisterSystem<System>();   
    SetSystemSignature<System, Components...>();
    return system;
  }

};
