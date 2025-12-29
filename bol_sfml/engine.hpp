#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "position_c.hpp"
#include "sprite_c.hpp"
#include <SFML/Graphics.hpp>
#include <flecs.h>

class engine
{
private:
  sf::RenderWindow w;
  const sf::Texture packed;
  flecs::world world;

public:
  engine();

  bool is_open() const;

  void handel_event();
  void draw();
  void draw(sprite_c &s, position_c &p);
};

#endif
