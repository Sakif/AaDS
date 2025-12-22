#include "display_matrix.hpp"

using namespace sf;

display_matrix::display_matrix(Vector2<unsigned> screen_size)
    : packed("asset/mono_packed.png"),
      tile_size(16, 16),
      display_dimensions(screen_size / tile_size.x),
      matrix(display_dimensions.x * display_dimensions.y)
{
}

Sprite
display_matrix::sprite_at(const unsigned int x, const unsigned int y) const
{
  display_sprite ds = matrix.at(x * display_dimensions.y + y);
  Sprite s(packed, ds.packed_rect(tile_size));
  s.setColor(ds.get_colour());
  s.setPosition(Vector2<float>(x, y) * static_cast<float>(tile_size.x));
  return s;
}

void
display_matrix::set_at(const display_sprite &ds, unsigned x, unsigned y)
{
  matrix.at(x * display_dimensions.y + y) = ds;
}

Vector2<unsigned>
display_matrix::get_dimention() const
{
  return display_dimensions;
}
