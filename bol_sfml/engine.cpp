#include "engine.hpp"
#include "c_position.hpp"
#include "c_sprite.hpp"
#include <SFML/Window/Keyboard.hpp>

using namespace sf;

namespace engine
{
RenderWindow main_window;
Texture packed;
flecs::world world;

RenderWindow *
get_window()
{
  return &main_window;
}

void
init()
{
  main_window = RenderWindow(VideoMode({1280, 720}), "Bushes of Love");
  main_window.setFramerateLimit(30);
  main_window.setVerticalSyncEnabled(true);
  packed = Texture("asset/mono_packed.png");

  world.entity("Player")
      .add<c_sprite>()
      .set<c_position>({0, 10});
}

void
draw_sprite(const c_sprite &s, const c_position &p)
{
  Vector2<float> pos = p.pos();
  Vector2<unsigned> window_size = main_window.getSize();
  if (pos.x > window_size.x && pos.y > window_size.y)
  {
    return;
  }

  Sprite sp(packed, s.rect());
  sp.setColor(s.colour);
  sp.setPosition(pos);
  main_window.draw(sp);
}

void
handel_event()
{
  while (std::optional<Event> e = main_window.pollEvent())
  {
    if (e->is<Event::Closed>())
    {
      main_window.close();
    }
    else if (const sf::Event::KeyPressed *key = e->getIf<Event::KeyPressed>())
    {
      if (key->scancode == Keyboard::Scancode::Escape)
      {
        main_window.close();
      }
      else if (key->scancode == Keyboard::Scancode::Up)
      {
        auto player = world.lookup("Player");
        auto pos = player.get_mut<c_position>();
        pos.y--;
        player.assign<c_position>(pos);
      }
    }
  }
}

void
draw()
{
  main_window.clear();
  world.each(draw_sprite);
  main_window.display();
}

} // namespace engine
