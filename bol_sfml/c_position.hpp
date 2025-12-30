#ifndef C_POSITION_HPP
#define C_POSITION_HPP

#include <SFML/System/Vector2.hpp>

struct c_position
{
  unsigned x, y;

  sf::Vector2<float> pos() const;
};

#endif
