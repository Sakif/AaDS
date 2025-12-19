#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "display_matrix.hpp"

class engine
{
private:
  sf::RenderWindow w;
  const sf::Texture packed;
  const sf::Vector2<unsigned> tile_size;
  display_matrix console;

public:
  engine();
  bool is_open() const;

  void handel_event();
  void draw();
};

#endif
