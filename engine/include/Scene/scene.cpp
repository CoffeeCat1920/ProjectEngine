#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>

struct Scene {
  std::string name;
};

using SceneId = size_t; 

class SceneManager {
  
private:
  std::unordered_map<SceneId, Scene> idToScene;
  std::unordered_map<std::string, SceneId> nameToId;
  
public:

  void AddScene() {}
  void RemoveScene() {}
};
