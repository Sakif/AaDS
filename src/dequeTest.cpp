#include "resizableDeque.hpp"
#include <iostream>

using namespace std;

int main() {
  auto queue = new resizableDeque<int>();
  cout << "Size: " << queue->size() << endl;
  cout << "Empty: " << queue->empty() << endl;
  delete queue;
  return 0;
}