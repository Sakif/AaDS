#include "c_position.hpp"
#include "c_sprite.hpp"

using namespace sf;

static const Vector2<int> tile_size(16, 16);

c_sprite::c_sprite(unsigned _x, unsigned _y, Color c)
    : x(_x),
      y(_y),
      colour(c) {}

Rect<int>
c_sprite::rect() const
{
  Vector2<int> start_position(x, y);
  start_position *= tile_size.x;
  Rect<int> placeholder(start_position, tile_size);
  return placeholder;
}

Vector2<float>
c_position::pos() const
{
  Vector2<float> placeholder(x, y);
  return placeholder.componentWiseMul(Vector2<float>(tile_size));
}
