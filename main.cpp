#include "raylib/raylib.h"
#include "core/colors.hpp"

int main () {
  
  InitWindow( 64*5 , 64*5, "Animation Test");
  SetTargetFPS(60);

  while ( !WindowShouldClose() )
  { 

    BeginDrawing();

    ClearBackground(GRUVBOX_DARK0);

    EndDrawing();
    
  }

  CloseWindow();

  return 0;
}
