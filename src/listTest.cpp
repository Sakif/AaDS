#include "doubleSentinelList.hpp"
#include <iostream>

using namespace std;
/* ✓ ✗ */

int main() {
  cout << "" << endl;
  cout << "Double Sentinels List Test" << endl;
  doubleSentinelList<int> list;
  cout << "Size: " << list.size() << endl;
  cout << "Empty: " << list.empty() << endl;
  try {
    list.front();
  } catch (underflow) {
    cout << "Underflow caught!" << endl;
  }
  try {
    list.back();
  } catch (underflow) {
    cout << "Underflow caught!" << endl;
  }
  auto node = list.begin();
  cout << "Node next: " << (node->next() == nullptr ? "✓" : "✗") << endl;
  list.pushFront(5);
  cout << "Front: " << list.front() << endl;
  cout << "Back: " << list.back() << endl;
  list.pushBack(7);
  cout << "Front: " << list.front() << endl;
  cout << "Back: " << list.back() << endl;
  cout << "Count 7: " << list.count(7) << endl;
  cout << "Count 6: " << list.count(6) << endl;
  cout << "Pop back: " << list.popBack() << endl;
  cout << "Count 7: " << list.count(7) << endl;
  node = list.begin();
  cout << "Node value: " << node->value() << endl;
  node = node->next();
  cout << "Node next: " << (node->next() == nullptr ? "✓" : "✗") << endl;
  cout << "Erase 5: " << list.erase(5) << endl;
  cout << "Empty: " << list.empty() << endl;
  cout << "Size: " << list.size() << endl;
  return 0;
}
