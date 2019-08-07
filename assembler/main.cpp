#include "Globals.h"
#include "Pass1.h"
#include "Pass2.h"

int main(int argc, char *argv[]) {
  init_globals(argv[1]);
  if (Pass1(argv[1])) {
    if (Pass2(argv[1]))
      cout << "Assembly completed successfully..." << endl;
    else {
      cout << "Pass 2 failed... program terminates..." << endl;
    }
  } else
    cout << "Pass 1 failed... program terminates..." << endl;
  return 0;
}
