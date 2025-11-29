/**
 * Rogue Like (RL) Engine
 */
#ifndef RL_ENGINE_HPP
#define RL_ENGINE_HPP

#include <SFML/Graphics.hpp>

class rl_engine
{
private:
  void handle_events();

public:
  sf::RenderWindow main_window;

  rl_engine();
  void run();
};

#endif
