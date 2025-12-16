#include "constants.hpp"

int
main()
{
  auto c = window_size.componentWiseDiv(tile_size);
  auto tot = c.x * c.y;
  return 0;
}
