#pragma once
#include "ECS/entity/entity.hpp"
#include <ECS/ECS.h>
#include <any>
#include <cassert>
#include <core/setting.hpp>
#include <functional>
#include <json_util.hpp>
#include <raylib.h>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>

class ComponentRegistry {
private:
  using DeserializeFunc = std::function<std::any(const json &)>;
  using SerializerFunc = std::function<json(const std::any &)>;
  using AdderFunc = std::function<void(Entity, const json &)>;

  struct ComponentOps {
    DeserializeFunc deserialize;
    SerializerFunc serialize;
    AdderFunc adder;
  };

  std::unordered_map<std::string, ComponentOps> operations;
  ECS &gEcs = ECS::Instance();

  ComponentRegistry() { operations.reserve(MAX_COMPONENTS); }

public:
  static ComponentRegistry &Instance() noexcept {
    static ComponentRegistry instance;
    return instance;
  }

  template <typename T> void Register(const std::string &name) {
    gEcs.RegisterComponent<T>();

    ComponentOps ops;
    ops.deserialize = [](const json &j) -> std::any { return j.get<T>(); };

    ops.serialize = [](const std::any &obj) -> json {
      return std::any_cast<const T &>(obj);
    };

    ops.adder = [this](Entity entity, const json &componentJson) {
      T comp = componentJson.get<T>();
      gEcs.AddComponent(entity, std::move(comp));
    };

    operations.emplace(name, std::move(ops));
  }

  void AddComponent(Entity entity, std::string_view name, const json &j) {
    if (auto it = operations.find(std::string(name)); it != operations.end()) {
      it->second.adder(entity, j);
    }
  }

  std::any Deserialize(std::string_view name, const json &j) {
    if (auto it = operations.find(std::string(name)); it != operations.end()) {
      return it->second.deserialize(j);
    } else {
      throw std::runtime_error(std::string("Component not registered: ") +
                               std::string(name));
    }
  }

  nlohmann::json Serialize(std::string_view name, const std::any &obj) {
    if (auto it = operations.find(std::string(name)); it != operations.end()) {
      return it->second.serialize(obj);
    } else {
      throw std::runtime_error(std::string("Component not registered: ") +
                               std::string(name));
    }
  }
};

#define REFLECTION(Type)                                                       \
  namespace {                                                                  \
  struct Type##_Registrar {                                                    \
    Type##_Registrar() {                                                       \
      ComponentRegistry::Instance().Register<Type>(#Type);                     \
    }                                                                          \
  };                                                                           \
  static Type##_Registrar Type##_registrar_;                                   \
  }
