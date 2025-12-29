#ifndef DISPLAY_SPRITE_HPP
#define DISPLAY_SPRITE_HPP

#include <SFML/Graphics.hpp>

class display_sprite
{
public:
  sf::Vector2<unsigned> index;
  sf::Color colour;

  /* Constructor */
  display_sprite(sf::Vector2<unsigned> i = {0, 0}, sf::Color c = sf::Color::White);

  /* Accessors */
  sf::Rect<int> packed_rect(const sf::Vector2<unsigned> tile_size) const;
  sf::Color get_colour() const;
};

#endif
