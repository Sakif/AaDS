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

  list.pushFront(9);
  list.pushFront(7);
  list.pushFront(5);
  list.pushFront(3);

  cout << "List 2" << endl;
  auto list2 = list;
  cout << "Size: " << list2.size() << endl;
  cout << "Front (3): " << list2.front() << endl;
  cout << "Back (9): " << list2.back() << endl;
  list2.pushFront(1);
  cout << "Size: " << list2.size() << endl;
  cout << "Front (1): " << list2.front() << endl;
  list2.popBack();
  list2.popFront();
  cout << "End of List 2" << endl;

  cout << "Size: " << list.size() << endl;
  cout << "Front (3): " << list.front() << endl;
  while (!list.empty())
    list.popBack();
  cout << "Size: " << list.size() << endl;
  node = list.begin();
  cout << "Node next: " << (node->next() == nullptr ? "✓" : "✗") << endl;
  node = node->previous();
  cout << "Node previous: " << (node->previous() == nullptr ? "✓" : "✗") << endl;
  list.pushFront(7);
  list.pushFront(3);
  list.pushBack(9);
  list.pushBack(11);
  cout << "Size: " << list.size() << endl;
  return 0;
}
