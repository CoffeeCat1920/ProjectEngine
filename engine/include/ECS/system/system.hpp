#pragma once

#include <ECS/entity/entity.hpp>
#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <vector>

struct System {
  std::vector<Entity> entities;
  virtual ~System() = default;    
  virtual void Do() = 0;
  System();
  System(std::vector<Entity> entities) : 
    entities(entities) 
  {}
};

using SystemId = size_t;

class SystemManager {
  
private:
  std::map<SystemId, std::shared_ptr<System>> systems;
  std::map<std::string, SystemId> nameToId;

  SystemId nextId = 0;

public:

  template<typename T>
  void RegisterSystem(EntityVec entities) {
    std::string name = typeid(T).name();
    nameToId[name] = nextId;
    systems[nextId] = std::make_shared<T>(entities);
    nextId++;
  }

  template<typename T>
  const std::shared_ptr<T> GetSystem() const {
    std::string name = typeid(T).name();
    const SystemId systemId = nameToId.at(name); 
    const auto& system = systems.at(systemId);
    return system;
  }
};
