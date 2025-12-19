#include "engine.hpp"
#include "display_sprite.hpp"
#include <SFML/System/Vector2.hpp>

using namespace sf;

engine::engine()
    : w(
          VideoMode({1280, 800}),
          "Wee",
          Style::Close),
      packed("asset/mono_packed.png"),
      tile_size(16, 16),
      console(w.getSize())
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
  display_sprite at({41, 20}, Color::Red); /* at {41, 20} */

  console.set_at(at, 5, 7);
  Sprite s(packed);
  for (auto x = 0U; x < 80; x++)
  {
    for (auto y = 0U; y < 50; y++)
    {
      auto ds = console.at(x, y);
      s.setTextureRect(ds.packed_rect(tile_size));
      s.setColor(ds.get_colour());
      s.setPosition(Vector2<float>(tile_size).componentWiseMul({static_cast<float>(x), static_cast<float>(y)}));
      w.draw(s);
    }
  }

  // s.setTextureRect(at.packed_rect(tile_size));
  // s.setColor(at.get_colour());
  // w.draw(s);

  w.display();
}
