#include "display_matrix.hpp"
#ifdef DEBUG
#include <cstdio>
#endif

using namespace sf;

display_matrix::display_matrix(Vector2<unsigned> screen_size)
    : tile_size(16, 16),
      display_dimensions(screen_size / tile_size.x),
      matrix(display_dimensions.x * display_dimensions.y)
{
#ifdef DEBUG
  printf("Screen size: %ux%u\n", screen_size.x, screen_size.y);
  printf("Display dimensions: %ux%u\n", display_dimensions.x, display_dimensions.y);
#endif
}

display_sprite
display_matrix::at(unsigned x, unsigned y) const
{
  return matrix.at(x * display_dimensions.y + y);
}

void
display_matrix::set_at(const display_sprite &ds, unsigned x, unsigned y)
{
  matrix.at(x * display_dimensions.y + y) = ds;
}
