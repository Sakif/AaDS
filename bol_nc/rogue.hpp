#ifndef ROGUE_HPP
#define ROGUE_HPP

#include <cstdlib>
#include <ctime>
#include <ncurses.h>

#define MAP_HEIGHT 25
#define MAP_WIDTH 100

typedef struct
{
  int y;
  int x;
} Position;

typedef struct
{
  Position pos;
  char ch;
} Entity;

typedef struct
{
  char ch;
  bool walkable;
} Tile;

typedef struct
{
  int height;
  int width;
  Position pos;
  Position center;
} Room;

// externs
extern Entity *player;

extern Tile **map;

Entity *createPlayer(Position start_pos);
void handleInput(int input);

void cursesSetup(void);
void gameLoop(void);
void closeGame(void);

Tile **createMapTiles(void);
Position setupMap(void);
void freeMap(void);

void drawMap(void);
void drawEntity(Entity *entity);
void drawEverything(void);

Room createRoom(int y, int x, int height, int width);
void addRoomToMap(Room room);

int window_a();
int menu();

#endif
