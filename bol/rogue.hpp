#ifndef ROGUE_HPP
#define ROGUE_HPP

#include <ncurses.h>
#include <stdlib.h>

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

#endif
