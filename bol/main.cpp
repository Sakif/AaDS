#include "rogue.hpp"

Entity *player;
Tile **map;

int
main()
{
  Position start_pos;
  cursesSetup();

  map = createMapTiles();
  start_pos = setupMap();
  player = createPlayer(start_pos);

  gameLoop();

  closeGame();
  return EXIT_SUCCESS;
}
