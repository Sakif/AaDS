#include "engine.hpp"
#include "display_sprite.hpp"

using namespace sf;

engine::engine()
    : w(
          VideoMode({1280, 720}),
          "Wee"),
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
  while (std::optional<Event> e = w.pollEvent())
  {
    if (e->is<Event::Closed>())
    {
      w.close();
    }
    else if (const sf::Event::KeyPressed *key = e->getIf<Event::KeyPressed>())
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
  display_sprite at({41, 20}, Color::Red); /* at gliph {41, 20} */
  console.set_at(at, 5, 7);

  for (unsigned x = 0; x < console.get_dimention().x; x++)
  {
    for (unsigned y = 0; y < console.get_dimention().y; y++)
    {
      Sprite sp = console.sprite_at(x, y);
      w.draw(sp);
    }
  }

  w.display();
}
