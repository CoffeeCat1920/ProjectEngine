#pragma once

#include <ECS/entity/entity.hpp>
#include <ECS/component/component.hpp>
#include <cameraController/cameraController.hpp>
#include <raylib.h>
#include <string>

constexpr int DEFAULT_SCALE = 4;

struct WindowConfig {
  int blockSize = 32;      
  int width = 10;           
  int height = 6;           
  int scale = DEFAULT_SCALE;

  WindowConfig() = default;
  WindowConfig(int block, int w, int h, int s = DEFAULT_SCALE) : 
    blockSize(block), 
    width(w), 
    height(h), 
    scale(s) 
  {}

  int rendering_width() const {
    return width * blockSize * scale;
  }

  int rendering_height() const {
    return height * blockSize * scale;
  }
};

class GameEngine {
  
private:
  const WindowConfig windowConfig;
  const std::string title = "Window";
  CameraController cameraController;

  EntityManager entityManager;
  ComponentManager componentManager;

  Entity e;

  void Update();
  void Draw();

public:
  GameEngine(std::string title = "title") :
    title(title)
  {}

  explicit GameEngine(const WindowConfig& config, std::string title = "title") : 
    windowConfig(config),
    title(title),
    cameraController(windowConfig.scale)
  {}

  void SMovement();
  void SRender();

  void Init();
  void Run();
};
