#include "display_sprite.hpp"

using namespace sf;

display_sprite::display_sprite(Vector2<unsigned> i, Color c)
    : index(i),
      colour(c)
{
}

Rect<int>
display_sprite::packed_rect(const Vector2<unsigned> tile_size) const
{
  Vector2<unsigned> start = index.componentWiseMul(tile_size);
  return Rect<int>({Vector2<int>(start), Vector2<int>(tile_size)});
}

Color
display_sprite::get_colour() const
{
  return colour;
}
