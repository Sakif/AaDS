#include "display_sprite.hpp"
#include <SFML/Graphics/Rect.hpp>

using namespace sf;
display_sprite::display_sprite(Vector2<unsigned> i)
    : index(i)
{
}

Vector2<int>
display_sprite::packed_start_index(const Vector2<unsigned> tile_size) const
{
  Vector2<unsigned> i = index.componentWiseMul(tile_size);
  return Vector2<int>(i);
}

Rect<int>
display_sprite::packed_rect(const Vector2<unsigned> tile_size) const
{
  auto start = index.componentWiseMul(tile_size);
  return Rect<int>({Vector2<int>(start), Vector2<int>(tile_size)});
}
