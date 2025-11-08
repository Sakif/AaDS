#include "rogue.hpp"
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;

int
window_a()
{
  initscr();
  auto win = newwin(10, 30, 5, 5);
  // Create a new window
  box(win, 0, 0);
  // Draw a border around the window
  mvwprintw(win, 3, 3, "Inside the Window");
  refresh();
  // Print text in the window
  wrefresh(win);
  // Refresh the window to display changes
  getch();
  delwin(win);
  // Delete the window
  endwin();

  return EXIT_SUCCESS;
}

int
menu()
{
  initscr();
  int rows, cols;

  for (int x = 0; x < COLS; ++x)
  {
    clear();
    mvprintw(5, x, "Moving Text");
    refresh();
    usleep(5000); // Delay in microseconds
  }

  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  start_color();                        // Enable color mode
  init_pair(1, COLOR_RED, COLOR_BLACK); // Define a color pair (foreground, background)

  const vector<string> menu = {
      "Option 1: View Item  ",
      "Option 2: Add Item   ",
      "Option 3: Delete Item",
      "Exit                 "};

  unsigned highlight = 0;
  int choice;

  while (1)
  {
    getmaxyx(stdscr, rows, cols);
    clear();
    for (unsigned i = 0; i < menu.size(); ++i)
    {
      if (i == highlight)
      {
        attron(A_REVERSE);
      }
      mvprintw(i + 1, 2, "%s", menu[i].c_str());
      if (i == highlight)
      {
        attroff(A_REVERSE);
      }
    }
    const string m = "Resize the terminal!";
    mvprintw(rows / 2, (cols - m.size()) / 2, "%s", m.c_str());
    refresh();
    refresh();
    choice = getch();

    switch (choice)
    {
    case KEY_UP:
      highlight = (highlight == 0) ? menu.size() - 1 : highlight - 1;
      break;
    case KEY_DOWN:
      highlight = (highlight == menu.size() - 1) ? 0 : highlight + 1;
      break;
    case 10:
      if (highlight == menu.size() - 1)
      {
        endwin();
        return 0;
      }
      attron(COLOR_PAIR(1)); // Apply color pair
      mvprintw(menu.size() + 2, 1, "You selected: %s", menu[highlight].c_str());
      attroff(COLOR_PAIR(1)); // Turn off the color
      refresh();
      getch();
      break;
    }
  }

  endwin();
  return EXIT_SUCCESS;
}
