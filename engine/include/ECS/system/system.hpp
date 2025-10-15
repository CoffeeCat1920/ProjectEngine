#pragma once

#include <ECS/component/component.hpp>
#include <ECS/entity/entity.hpp>
#include <ECS/utils/signatures.hpp>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <pstl/glue_algorithm_defs.h>
#include <string>
#include <unordered_map>

using SystemId = size_t;

struct System {
  std::set<Entity> entities;
  Signature signature;
  virtual void Update() = 0;
};

class SystemManager {
  
private:
  std::unordered_map<std::string, std::shared_ptr<System>> systems;

public:

  template <typename T>
  std::shared_ptr<T> RegisterSystem() {
    const std::string typeName = typeid(T).name();
    assert(systems.find(typeName) == systems.end() && "Registering system more than once.");
    auto system = std::make_shared<T>();
    systems.insert({typeName, system});
    std::cout << "Registered system: " << typeName << "\n";
    return system;
  }

  template <typename T>
  void SetSignature(Signature signature) {
    const std::string typeName = typeid(T).name();
    auto system = systems.find(typeName); 
    assert(system != systems.end() && "System used before registering");
    system->second->signature = signature;
  }

  template <typename T>
  void SetSignature(ComponentId componentId) {
    const std::string typeName = typeid(T).name();
    auto system = systems.find(typeName);
    assert(system != systems.end() && "System used before registering");
    Signature signature = signatureUtils::GetSignature(componentId); 
    system->second->signature = signature;
  }

  template<typename T>
  void SetSignature(std::initializer_list<ComponentId> componentIds) {
    const std::string typeName = typeid(T).name();
    auto system = systems.find(typeName);
    assert(system != systems.end() && "System used before registering");
    Signature signature = signatureUtils::GetSignature(componentIds);
    std::cout << "Setting signature:" << signature << " for component " << typeName << std::endl;
    system->second->signature = signature;
  }

  void EntityDestroyed(Entity entity) {
		for (auto const& pair : systems)
		{
			auto const& system = pair.second;
			system->entities.erase(entity);
		}
  }

  void EntitySignatureChanged(Entity entity, Signature signature) {
    for (const auto& pair : systems) {
      const auto& system = pair.second;
      const auto& systemSignature = system->signature;

      if ((signature & systemSignature) == systemSignature) {
        system->entities.insert(entity);
      } else {
        system->entities.erase(entity);
      }
    }
  }

};
