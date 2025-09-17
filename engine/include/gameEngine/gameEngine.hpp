#pragma once

#include "ECS/entity/entity.hpp"
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

  void Update();
  void Draw();

public:
  GameEngine() = default;
  explicit GameEngine(const WindowConfig& config, std::string title = "title") : 
    windowConfig(config),
    title(title),
    cameraController(windowConfig.scale)
  {}

  void Init();
  void Run();
};
