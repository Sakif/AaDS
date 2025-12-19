#ifndef DISPLAY_SPRITE_HPP
#define DISPLAY_SPRITE_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class display_sprite
{
private:
  const sf::Vector2<unsigned> index;

public:
  display_sprite(sf::Vector2<unsigned> i = {0, 0});

  sf::Vector2<int> packed_start_index(const sf::Vector2<unsigned> tile_size) const;
  sf::Rect<int> packed_rect(const sf::Vector2<unsigned> tile_size) const;
};

#endif
