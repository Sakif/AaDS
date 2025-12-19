#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>

class engine
{
private:
  sf::RenderWindow w;

public:
  engine();
  bool is_open() const;

  void handel_event();
  void draw();
};

#endif
