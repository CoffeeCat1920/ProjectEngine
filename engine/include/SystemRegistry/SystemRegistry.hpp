#pragma once

#include "ECS/system/system.hpp"
#include <cassert>
#include <memory>
#include <string>
#include <unordered_map>

class SystemRegistery {
  
private:
  std::unordered_map<std::string, std::shared_ptr<System>> physicsSystemsRegister;
  std::unordered_map<std::string, std::shared_ptr<System>> renderSystemsRegister;
  SystemRegistery() = default;

public:
  SystemRegistery(const SystemRegistery&) = delete;
  SystemRegistery& operator=(const SystemRegistery&) = delete;
  SystemRegistery(SystemRegistery&&) = delete;
  SystemRegistery& operator=(SystemRegistery&&) = delete;

  static SystemRegistery& Instance() {
    static SystemRegistery systemRegistry;
    return systemRegistry;
  }

  template<typename T> 
  void RegisterPhysicsSystem(const std::string& name) {
    assert(physicsSystemsRegister.find(name) == physicsSystemsRegister.end() && "System already registered");
    auto system = std::make_shared<T>();
    physicsSystemsRegister[name] = system;
  }

  template<typename T> 
  void RegisterRenderSystem(const std::string& name) {
    assert(physicsSystemsRegister.find(name) == physicsSystemsRegister.end() && "System already registered");
    auto system = std::make_shared<T>();
    physicsSystemsRegister[name] = system;
  }

}; 

#define SYSTEM_PHYSICS_REGISTERATION(TYPE)\
  struct TYPE##_REGISTERER {\
    TYPE##_REGISTERER() {\
      SystemRegistery::Instance().RegisterPhysicsSystem<TYPE>(#TYPE);\
    }\
  };\
  static TYPE##_REGISTERER TYPE##_REGISTERER_;

#define SYSTEM_RENDER_REGISTERATION(TYPE)\
  struct TYPE##_REGISTERER {\
    TYPE##_REGISTERER() {\
      SystemRegistery::Instance().RegisterRenderSystem<TYPE>(#TYPE);\
    }\
  };\
  static TYPE##_REGISTERER TYPE##_REGISTERER_;
