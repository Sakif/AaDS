#include "engine.hpp"
#include "display_sprite.hpp"

using namespace sf;

engine::engine()
    : w(
          VideoMode({1280, 800}),
          "Wee",
          Style::Close),
      packed("asset/mono_packed.png"),
      tile_size({16, 16}),
      console(w.getSize().componentWiseDiv(tile_size))
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
    else if (auto key = e->getIf<Event::KeyPressed>())
    {
      if (key->scancode == Keyboard::Scancode::Escape)
      {
        w.close();
      }
    }
  }
}

void
engine::draw()
{
  w.clear();
  display_sprite at({41, 20});
  Sprite s(packed, at.packed_rect(tile_size));
  s.setColor(Color::Green);
  w.draw(s);
  w.display();
}
