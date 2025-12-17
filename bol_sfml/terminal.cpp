#include "terminal.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

terminal::terminal()
    : array(console.x * console.y) {}

void
terminal::draw(RenderWindow &w)
{
  for (Vector2<int> s : array)
  {
    Rect<int> tile(s.componentWiseMul(tile_size), tile_size);
    Sprite sp(packed, tile);
    w.draw(sp);
  }
}
