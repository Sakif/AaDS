#ifndef DISPLAY_MATRIX_HPP
#define DISPLAY_MATRIX_HPP

#include "display_sprite.hpp"

class display_matrix
{
private:
  const sf::Texture packed;
  const sf::Vector2<unsigned> tile_size;
  const sf::Vector2<unsigned> display_dimensions;
  std::vector<display_sprite> matrix;

public:
  /* constructor */
  display_matrix(sf::Vector2<unsigned> screen_size);

  /* accessor */
  sf::Sprite sprite_at(const unsigned x, const unsigned y) const;
  sf::Vector2<unsigned> get_dimention() const;

  /* mutator */
  void set_at(const display_sprite &ds, const unsigned x, const unsigned y);
};

#endif
