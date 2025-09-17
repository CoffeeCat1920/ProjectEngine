#include "raylib/raylib.h"
#include "core/colors.hpp"

#include "game/game.hpp"

int main () {
  
  InitWindow( 64*5 , 64*5, "Animation Test");
  Game game;

  while ( !WindowShouldClose() )
  { 

    game.Update();

    BeginDrawing();

    ClearBackground(GRUVBOX_DARK0);

    game.Draw();

    EndDrawing();
    
  }

  CloseWindow();

  return 0;
}
