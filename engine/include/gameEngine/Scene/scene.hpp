#pragma once

#include "core/setting.hpp"
#include "gameEngine/Component/Component.hpp"
#include <cstdint>
#include <filesystem>
#include <stack>
#include <unordered_map>


using SceneId = uint8_t; 

struct Scene {
  SceneId id{};
  json name; 
  Scene() = default;
  Scene(std::filesystem::path path, SceneId id) :
    id(id)
  {}
};

class SceneManager {
  
private:
  std::unordered_map<SceneId, Scene> scenes;
  std::stack<SceneId> sceneIds;

public:
  SceneManager() {
    for (uint8_t i = 0; i <= MAX_SCENES; i++ ) {
      sceneIds.push(i); 
    }
  }

  SceneId AddScene(std::filesystem::path path) {
     
  }

};
