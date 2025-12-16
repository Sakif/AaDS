#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "constants.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class terminal
{
private:
  const sf::Vector2<unsigned int> console = window_size.componentWiseDiv(tile_size);
  std::vector<sf::Vector2<int>> array;

public:
  void draw(sf::RenderWindow &w);
};

#endif
