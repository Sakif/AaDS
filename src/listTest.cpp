#include "doubleSentinelList.hpp"
#include <iostream>

using namespace std;
/* ✓ ✗ */

int main() {
  cout << "" << endl;
  cout << "Double Sentinels List Test" << endl;
  doubleSentinelList<int> list;
  list.pushBack(7);
  list.pushBack(2);
  list.pushBack(1);
  list.pushBack(6);
  list.pushBack(8);
  list.pushBack(5);
  list.pushBack(3);
  list.pushBack(4);
  cout << list << endl;
  list.sort();
  cout << "Sorted list" << endl;
  cout << list << endl;
  return 0;
}
