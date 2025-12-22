#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "display_matrix.hpp"

class engine
{
private:
  sf::RenderWindow w;
  display_matrix console;

public:
  engine();
  bool is_open() const;

  void handel_event();
  void draw();
};

#endif
