#pragma once

#include "ECS/component/component.hpp"
#include <ECS/entity/entity.hpp>
#include <cassert>
#include <cstddef>
#include <memory>
#include <pstl/glue_algorithm_defs.h>
#include <string>
#include <unordered_map>

struct System {
  std::set<Entity> entities;
};

using SystemId = size_t;

class SystemManager {
  
private:
  std::unordered_map<std::string, Signature> signatures;
  std::unordered_map<std::string, std::shared_ptr<System>> systems;

public:

  template <typename T>
  std::shared_ptr<T> RegisterSystem() {
    const std::string typeName = typeid(T).name();
    assert(systems.find(typeName) == systems.end() && "Registering system more than once.");
    auto system = std::make_shared<T>();
    systems.insert({typeName, system});
    return system;
  }

  template <typename T>
  void SetSignature(Signature signature) {
    const std::string typeName = typeid(T).name();
    assert(systems.find(typeName) != systems.end() && "System used before registering");
    signatures.insert({typeName, signature});
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
      const auto& type = pair.first;
      const auto& system = pair.second;
      const auto& systemSignature = signatures[type];

      if ((signature & systemSignature) == systemSignature) {
        system->entities.insert(entity);
      } else {
        system->entities.erase(entity);
      }
    }
  }

};
