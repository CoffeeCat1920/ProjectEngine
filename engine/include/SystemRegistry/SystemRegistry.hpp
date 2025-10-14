#pragma once

#include <ECS/system/system.hpp>
#include <ECS/ECS.h>
#include <cassert>
#include <memory>
#include <string>
#include <unordered_map>


enum class SystemType { Physics, Render };

class SystemRegistry {
private:
    std::unordered_map<std::string, std::shared_ptr<System>> physicsSystemsRegister;
    std::unordered_map<std::string, std::shared_ptr<System>> renderSystemsRegister;
    ECS& gECS = ECS::Instance();

    SystemRegistry() = default;

    template<typename T>
    void RegisterSystemImpl(const std::string& name, SystemType type) {
        auto& reg = (type == SystemType::Physics) ? physicsSystemsRegister : renderSystemsRegister;
        assert(reg.find(name) == reg.end() && "System already registered");

        auto system = std::make_shared<T>();
        gECS.RegisterSystem<T>();  
        reg[name] = system;
    }

public:
    SystemRegistry(const SystemRegistry&) = delete;
    SystemRegistry& operator=(const SystemRegistry&) = delete;
    SystemRegistry(SystemRegistry&&) = delete;
    SystemRegistry& operator=(SystemRegistry&&) = delete;

    static SystemRegistry& Instance() {
      static SystemRegistry instance;
      return instance;
    }

    template<typename T> void RegisterPhysicsSystem(const std::string& name) {
      RegisterSystemImpl<T>(name, SystemType::Physics);
    }

    template<typename T> void RegisterRenderSystem(const std::string& name) {
      RegisterSystemImpl<T>(name, SystemType::Render);
    }

    void PhysicsUpdate() {
      for (auto& [_, sys] : physicsSystemsRegister) sys->Update();
    } 

    void RenderUpdate() {
      for (auto& [_, sys] : renderSystemsRegister) sys->Update();
    }
};


#define REGISTER_SYSTEM(TYPE, CATEGORY)\
  namespace {\
    struct TYPE##_AutoRegister {\
      TYPE##_AutoRegister() {\
        SystemRegistry::Instance()\
            .Register##CATEGORY##System<TYPE>(#TYPE); \
      }\
    };\
    static TYPE##_AutoRegister TYPE##_AutoRegister_;\
  }
