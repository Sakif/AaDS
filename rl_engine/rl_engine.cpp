#include "rl_engine.hpp"

using namespace sf;

int style = Style::Titlebar | Style::Close;

rl_engine::rl_engine()
    : main_window(VideoMode({1280, 800}),
                  "RL Engine", style)
{
  main_window.setVerticalSyncEnabled(true);
}

void
rl_engine::run()
{
  while (main_window.isOpen())
  {
    main_window.clear();
    handle_events();
    main_window.display();
  }
}

void
rl_engine::handle_events()
{
  while (std::optional<Event> e = main_window.pollEvent())
  {
    if (e->is<Event::Closed>())
    {
      main_window.close();
    }
    else if (const sf::Event::KeyPressed *kbd = e->getIf<Event::KeyPressed>())
    {
      if (kbd->scancode == Keyboard::Scancode::Escape)
      {
        main_window.close();
      }
    }
  }
}
