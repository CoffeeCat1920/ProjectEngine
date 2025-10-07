#pragma once

#include "gameEngine/Component/physics/CRigidBody.hpp"
#include "gameEngine/Component/render/CSprite.hpp"
#include "gameEngine/Component/render/CTransform.hpp"
#include <cassert>
#include <gameEngine/Component/physics/CGravity.hpp>
#include <gameEngine/Component/physics/Physics.hpp>
#include <gameEngine/Component/render/Render.hpp>

#include <map>
#include <raylib.h>
#include <json_util.hpp>
#include <string>
#include <typeindex>

class ComponentRegistry {

private:
  std::map<std::string, std::type_index> registry;

public:
  ComponentRegistry() {
    registry["CGravity"] = std::type_index(typeid(CGravity));
    registry["CRigidBody"] = std::type_index(typeid(CRigidBody));
    registry["CTransform"] = std::type_index(typeid(CTransform));
    registry["CSprite"] = std::type_index(typeid(CSprite));
  }

  const std::type_index &Get(const std::string &name) const {
    const auto it = registry.find(name);
    assert(it != registry.end() && "Invalid component call"); 
    return it->second;
  }
};
