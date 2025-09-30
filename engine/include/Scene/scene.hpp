#pragma once

#include "ECS/ECS.h"

class Scene {
  
private:
  ECS& gEcs;

public:

  Scene(ECS& gEcs) :
    gEcs(gEcs)
  {}

  virtual void Init() = 0;
  virtual void Update() = 0;
  virtual void Draw() = 0;
};
