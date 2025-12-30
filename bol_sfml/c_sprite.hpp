#ifndef C_SPRITE_HPP
#define C_SPRITE_HPP

#include <SFML/Graphics.hpp>

struct c_sprite
{
  unsigned x, y;
  sf::Color colour;

  c_sprite(unsigned _x = 41, unsigned _y = 20, sf::Color c = sf::Color::White);
  sf::Rect<int> rect() const;
};

#endif
