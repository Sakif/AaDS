#ifndef DISPLAY_MATRIX_HPP
#define DISPLAY_MATRIX_HPP

#include "display_sprite.hpp"

class display_matrix
{
private:
  const sf::Vector2<unsigned> tile_size;
  const sf::Vector2<unsigned> display_dimensions;
  std::vector<display_sprite> matrix;

public:
  display_matrix(sf::Vector2<unsigned> screen_size);

  display_sprite at(unsigned x, unsigned y) const;

  void set_at(const display_sprite &ds, unsigned x, unsigned y);
};

#endif
