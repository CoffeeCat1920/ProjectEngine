#pragma once

#include <ECS/entity/entity.hpp>
#include <cassert>
#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <vector>

struct System {
  std::vector<Entity> entities;
  virtual ~System() = default;    
  virtual void Do() const = 0;

  System() = default;
  explicit System(std::vector<Entity>& entities) 
    : entities(entities)
  {}
};

using SystemId = size_t;

class SystemManager {
private:
  std::map<SystemId, std::unique_ptr<System>> systems;
  std::map<std::string, SystemId> nameToId;
  SystemId nextId = 0;

  template<typename T>
  T* GetDerivedSystem() {
    std::string name = typeid(T).name();
    auto it = nameToId.find(name);
    assert(it != nameToId.end() && "System not registered.");
    return static_cast<T*>(systems[it->second].get());
  }

public:
  template<typename T>
  void RegisterSystem(const std::vector<Entity>& entities) {
    std::string name = typeid(T).name();
    assert(nameToId.find(name) == nameToId.end() && "System registered twice.");
    nameToId[name] = nextId;
    systems[nextId] = std::make_unique<T>(entities);
    nextId++;
  }

  template<typename T>
  T* GetSystem() {
    return GetDerivedSystem<T>();
  }

  template<typename T>
  const T* GetSystem() const {
    return GetDerivedSystem<T>();
  }
};
