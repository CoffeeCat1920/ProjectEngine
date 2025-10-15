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

    template<typename Component>
    void PrintType() {
      std::cout << "Registering System: " << typeid(Component).name() << std::endl;
    }

    template<typename T, typename... Components>
    void RegisterSystemImpl(const std::string& name, SystemType type) {
        auto& reg = (type == SystemType::Physics) ? physicsSystemsRegister : renderSystemsRegister;
        assert(reg.find(name) == reg.end() && "System already registered");
        auto system = std::make_shared<T>();
        gECS.RegisterSystemWithSignatures<T, Components...>();
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

    template<typename T, typename... Components> void RegisterPhysicsSystem(const std::string& name) {
      RegisterSystemImpl<T, Components...>(name, SystemType::Physics);
    }

    template<typename T, typename... Components> void RegisterRenderSystem(const std::string& name) {
      RegisterSystemImpl<T, Components...>(name, SystemType::Render);
    }

    void PhysicsUpdate() {
      for (auto& [_, sys] : physicsSystemsRegister) sys->Update();
    } 

    void RenderUpdate() {
      for (auto& [_, sys] : renderSystemsRegister) sys->Update();
    }
};

#define REGISTER_SYSTEM(TYPE, CATEGORY, ...)\
  namespace {\
    struct TYPE##_AutoRegister {\
      TYPE##_AutoRegister() {\
        SystemRegistry::Instance()\
            .Register##CATEGORY##System<TYPE,  ##__VA_ARGS__>(#TYPE); \
      }\
    };\
    static TYPE##_AutoRegister TYPE##_AutoRegister_;\
  }
