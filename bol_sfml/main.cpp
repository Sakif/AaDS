#include "constants.hpp"
#include <cstdio>

int
main()
{
  auto c = window_size.componentWiseDiv(tile_size);
  unsigned tot = c.x * c.y;
  printf("Total: %d\n", tot);
  return 0;
}
