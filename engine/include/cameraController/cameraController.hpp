#pragma once

#include "raylib.h"

class CameraController {
  
private:
Camera2D camera;
  
public:

  CameraController(float zoom = 4) {
    camera = Camera2D{
      .offset = { 0, 0 },
      .target = { 0, 0 },
      .rotation = 0.0f,
      .zoom = zoom
    };
  }

  Camera2D GetCamera(); 
};
