#include "engine.hpp"

using namespace sf;

engine::engine()
    : w(
          VideoMode({1280, 800}),
          "Wee",
          Style::Close)
{
  w.setFramerateLimit(60);
  w.setVerticalSyncEnabled(true);
}

bool
engine::is_open() const
{
  return w.isOpen();
}

void
engine::handel_event()
{
  while (auto e = w.pollEvent())
  {
    if (e->is<Event::Closed>())
    {
      w.close();
    }
  }
}

void
engine::draw()
{
  w.clear();
  w.display();
}
