#include "engine.hpp"

int
main()
{
  engine::init();

  auto w = engine::get_window();
  while (w->isOpen())
  {
    engine::handel_event();
    engine::draw();
  }

  return 0;
}
