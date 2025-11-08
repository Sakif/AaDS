#include "rogue.hpp"

Entity *player;
Tile **map;

int
main()
{
#ifdef DEBUG
  Position start_pos;
  cursesSetup();
  srand(time(NULL));

  map = createMapTiles();
  start_pos = setupMap();
  player = createPlayer(start_pos);

  gameLoop();

  closeGame();
#endif
  menu();

  return EXIT_SUCCESS;
}
