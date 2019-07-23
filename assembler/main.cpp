#include "Globals.h"
#include "Pass1.h"

int main(int argc, char *argv[]) {

  init_globals(argv[1]);
  if (Pass1(argv[1])) {
    cout << "Pass1 done" << endl;
  }
}
