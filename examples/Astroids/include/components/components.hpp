#pragma once

#include "raylib.h"

struct CProjectile {
  Vector2 velocity;
  float lifetime = 2.0f; // seconds before auto-destroy
};
