#include "engine.hpp"

using namespace sf;

engine::engine()
    : w(
          VideoMode({1280, 720}),
          "Wee"),
      packed("asset/mono_packed.png")
{
  w.setFramerateLimit(60);
  w.setVerticalSyncEnabled(true);

  world.entity("Player")
      .set<sprite_c>({41, 20, Color::White})
      .set<position_c>({5, 7});
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

  world.each([](sprite_c &s, position_c &p)
             { printf("Sprinte (%d, %d) %d\nPosition: (%d,%d)\n", s.x, s.y, s.colour.toInteger(), p.x, p.y); });

  // display_sprite at({41, 20}, Color::Red); /* at gliph {41, 20} */
  // console.set_at(at, 5, 7);

  w.display();
}
