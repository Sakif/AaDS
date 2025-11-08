#include "rogue.hpp"

Entity *
createPlayer(Position start_pos)
{
  auto newPlayer = new Entity;

  newPlayer->pos.y = start_pos.y;
  newPlayer->pos.x = start_pos.x;
  newPlayer->ch = '@';

  return newPlayer;
}

void
movePlayer(Position newPos)
{
  if (map[newPos.y][newPos.x].walkable)
  {
    player->pos.y = newPos.y;
    player->pos.x = newPos.x;
  }
}

void
handleInput(int input)
{
  Position newPos = {player->pos.y, player->pos.x};

  switch (input)
  {
  // move up
  case 'k':
    newPos.y--;
    break;
  // move down
  case 'j':
    newPos.y++;
    break;
  // move left
  case 'h':
    newPos.x--;
    break;
  // move right
  case 'l':
    newPos.x++;
    break;
  default:
    break;
  }

  movePlayer(newPos);
}
