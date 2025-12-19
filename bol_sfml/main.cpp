#include "engine.hpp"

int
main()
{
  engine game;

  while (game.is_open())
  {
    game.handel_event();
    game.draw();
  }

  return 0;
}
