#include "rogue.hpp"

Tile **
createMapTiles(void)
{
  auto tiles = (Tile **)calloc(MAP_HEIGHT, sizeof(Tile *));

  for (int y = 0; y < MAP_HEIGHT; y++)
  {
    tiles[y] = (Tile *)calloc(MAP_WIDTH, sizeof(Tile));
    for (int x = 0; x < MAP_WIDTH; x++)
    {
      tiles[y][x].ch = '#';
      tiles[y][x].walkable = false;
    }
  }

  return tiles;
}

void
connectRoomCenters(Position centerOne, Position centerTwo)
{
  Position temp;
  temp.x = centerOne.x;
  temp.y = centerOne.y;

  while (true)
  {
    if (abs((temp.x - 1) - centerTwo.x) < abs(temp.x - centerTwo.x))
      temp.x--;
    else if (abs((temp.x + 1) - centerTwo.x) < abs(temp.x - centerTwo.x))
      temp.x++;
    else if (abs((temp.y + 1) - centerTwo.y) < abs(temp.y - centerTwo.y))
      temp.y++;
    else if (abs((temp.y - 1) - centerTwo.y) < abs(temp.y - centerTwo.y))
      temp.y--;
    else
      break;

    map[temp.y][temp.x].ch = '.';
    map[temp.y][temp.x].walkable = true;
  }
}

Position
setupMap(void)
{
  int y, x, height, width, n_rooms;
  n_rooms = (rand() % 11) + 5;
  auto rooms = (Room *)calloc(n_rooms, sizeof(Room));
  Position start_pos;

  for (int i = 0; i < n_rooms; i++)
  {
    y = (rand() % (MAP_HEIGHT - 10)) + 1;
    x = (rand() % (MAP_WIDTH - 20)) + 1;
    height = (rand() % 7) + 3;
    width = (rand() % 15) + 5;
    rooms[i] = createRoom(y, x, height, width);
    addRoomToMap(rooms[i]);

    if (i > 0)
    {
      connectRoomCenters(rooms[i - 1].center, rooms[i].center);
    }
  }

  start_pos.y = rooms[0].center.y;
  start_pos.x = rooms[0].center.x;

  free(rooms);

  return start_pos;
}

bool
roomOverlaps(Room *rooms, int rooms_counter, int y, int x, int height, int width)
{
  for (int i = 0; i < rooms_counter; i++)
  {
    if (x >= rooms[i].pos.x + rooms[i].width || rooms[i].pos.x >= x + width)
    {
      continue;
    }
    if (y + height <= rooms[i].pos.y || rooms[i].pos.y + rooms[i].height <= y)
    {
      continue;
    }

    return true;
  }

  return false;
}

void
freeMap(void)
{
  delete[] map;
}
