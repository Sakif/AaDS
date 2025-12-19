#ifndef DISPLAY_MATRIX_HPP
#define DISPLAY_MATRIX_HPP

#include <SFML/Graphics.hpp>

class display_matrix
{
private:
  const sf::Vector2<unsigned> display_dimentions;

public:
  display_matrix(sf::Vector2<unsigned> dimentions);
  ~display_matrix();
};

#endif
