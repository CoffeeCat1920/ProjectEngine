#pragma once

#include "ComponentRegistry/ComponentRegistry.hpp"
#include "ECS/ECS.h"
#include "ECS/entity/entity.hpp"
#include <filesystem>
#include <fstream>
#include <string>

struct Scene {

private:
  json sceneData{};
  EntityVec entities{};
  ECS &gECS = ECS::Instance();
  ComponentRegistry &componentRegistry = ComponentRegistry::Instance();

  void CreateEntities() {
    if (!sceneData.contains("entities") || sceneData["entities"].empty())
      return;

    for (const auto &entityJson : sceneData["entities"]) {
      std::string name = entityJson.value("name", "Unnamed");
      Entity entity = gECS.AddEntity(name);

      if (!entityJson.contains("components") ||
          entityJson["components"].empty())
        continue;
      for (const auto &[componentName, componentData] :
           entityJson["components"].items()) {
        componentRegistry.AddComponent(entity, componentName, componentData);
      }
    }
  }

  void DeleteEntities() {}

public:
  Scene(const std::filesystem::path &scenePath) {
    std::ifstream inputFile(scenePath);
    if (!inputFile.is_open()) {
      throw std::runtime_error("Failed to open scene file: " +
                               scenePath.string());
    }

    inputFile >> sceneData;
    inputFile.close();

    CreateEntities();
  }
};
