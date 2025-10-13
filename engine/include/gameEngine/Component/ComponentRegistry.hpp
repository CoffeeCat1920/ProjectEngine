#pragma once

#include <any>
#include <cassert>
#include <functional>
#include <gameEngine/Component/physics/CGravity.hpp>
#include <gameEngine/Component/physics/Physics.hpp>
#include <gameEngine/Component/render/Render.hpp>

#include <raylib.h>
#include <json_util.hpp>
#include <string>
#include <unordered_map>

class ComponentRegistry {
private:
  ComponentRegistry() = default;
  std::unordered_map<std::string, std::function<std::any(const json&)>> deserializers_;   
  std::unordered_map<std::string, std::function<json(const std::any&)>> serializers_;
  
public:

  static ComponentRegistry& Instance() {
    static ComponentRegistry instance;
    return instance;
  }

  template<typename T>
  void Register(const std::string& name) {

    deserializers_[name] = [](const json& j) -> std::any {
      return j.get<T>();
    };

    serializers_[name] = [](std::any& obj) -> json {
      return nlohmann::json::object(
        { 
          {"type", typeid(T).name()}, 
          {"data", std::any_cast<const T&>(obj)} 
        }
      );
    };

  }


  std::any Deserialize(const std::string& name, const json& j) {
    return deserializers_.at(name)(j);
  }

  nlohmann::json Serialize(const std::string& name, const std::any& obj) {
    return serializers_.at(name)(obj);
  }
  
};
