#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <flecs.h>

namespace engine
{
sf::RenderWindow *get_window();

void init();
void handel_event();
void draw();
} // namespace engine

#endif
