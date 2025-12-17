#include "engine.hpp"
#include "constants.hpp"

using namespace sf;

auto win_size = Vector2<unsigned>(window_size);

engine::engine() : w(VideoMode(win_size), "Wee", State::Fullscreen)
{
  w.setFramerateLimit(60);
  w.setVerticalSyncEnabled(true);
}

bool
engine::is_open() const
{
  return w.isOpen();
}
