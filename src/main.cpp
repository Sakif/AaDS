#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <stdio.h>

using namespace sf;

int main()
{
  RenderWindow window(
      VideoMode::getDesktopMode(),
      "Bushes of Love");

#ifdef DEBUG
  printf("Window is of size (%d, %d)\n",
         window.getSize().x, window.getSize().y);
#endif

  CircleShape shapeC(100.0);
  RectangleShape shapeR(Vector2f(100.0, 200.0));
  shapeC.setFillColor(Color::Blue);
  shapeR.setFillColor(Color::Green);
  shapeR.setPosition(200.0, 0.0);

  bool mouseButtonReleased;
  while (window.isOpen())
  {
    Event e;
    while (window.pollEvent(e))
    {
      if (e.type == Event::KeyReleased)
      {
#ifdef DEBUG
        printf("A key was released!\n");
#endif

        printf("%d was pressed\n", e.key.code);
      }

      mouseButtonReleased = false;
      if (e.type == Event::MouseButtonReleased)
      {
        printf("Mouse button pressed!\n");
        mouseButtonReleased = true;
      }
    }

    if (Mouse::isButtonPressed(Mouse::Left) && mouseButtonReleased)
    {
      printf("Left Mouse Button was pressed\n");
    }

    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
      window.close();
    }

    window.clear();
    window.draw(shapeC);
    window.draw(shapeR);
    window.display();
  }

  return EXIT_SUCCESS;
}
