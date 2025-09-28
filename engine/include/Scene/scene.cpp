#pragma once

#include "ECS/component/component.hpp"
#include <ECS/entity/entity.hpp>

#include <cassert>
#include <cstddef>
#include <string>
#include <unordered_map>

class Scene {
  
private:
  std::string name;
  Signature signature;  

public:

  Scene(std::string name, Signature signature) :
    name(name),
    signature(signature)
  {}
  
};

using SceneId = size_t; 

class SceneManager {
  
private:
  std::unordered_map<SceneId, Scene> idToScene{};
  std::unordered_map<std::string, SceneId> nameToId{};


  SceneId nextId = 0;
  
public:

  void AddScene(std::string name, Signature signature) {
    assert(nameToId.find(name) == nameToId.end() && "Scene with name exists.");
    nameToId[name] = nextId;
    idToScene[nextId] = Scene {
      .name = name,
      .signature = signature
    };
  }

  void RemoveScene() {}
};
