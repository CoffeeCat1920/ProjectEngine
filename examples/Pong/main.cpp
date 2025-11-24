#include "./include/game/game.hpp"

int main() {
  WindowConfig config(16, 20, 10);
  Game game(config);
  game.Init();
  game.Run();
  return 0;
}
