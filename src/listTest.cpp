#include "doubleSentinelList.hpp"
using namespace std;

int main() {
  auto l = new doubleSentinelList<int>();
  cout << "List size: " << l->size() << endl;
  cout << "List empty: " << l->empty() << endl;

  /* tests for empty list */
  try {
    auto node = l->begin();
  } catch (underflow u) {
    cout << "underflow caught" << endl;
  }
  try {
    auto node = l->rbegin();
  } catch (underflow u) {
    cout << "underflow caught" << endl;
  }
  try {
    l->front();
  } catch (underflow u) {
    cout << "underflow caught" << endl;
  }
  try {
    l->back();
  } catch (underflow u) {
    cout << "underflow caught" << endl;
  }

  /* steping through empty list */
  auto node = l->rend();
  cout << "Head sentinel value: " << node->value() << endl;
  if (node->previous() == nullptr)
    cout << "previous good" << endl;
  if (node->next() == l->end())
    cout << "next good" << endl;
  node = l->end();
  cout << "Tail sentinel value: " << node->value() << endl;
  if (node->next() == nullptr)
    cout << "next good" << endl;
  if (node->previous() == l->rend())
    cout << "previous good" << endl;

  /* push front 7 */
  l->pushFront(7);
  cout << "List size: " << l->size() << endl;
  cout << "List empty: " << l->empty() << endl;

  /* tests for non empty list */
  cout << "List front: " << l->front() << endl;
  cout << "List back: " << l->back() << endl;
  /* push back 3 */
  l->pushBack(3);
  cout << "List front: " << l->front() << endl;
  cout << "List back: " << l->back() << endl;
  cout << "List size: " << l->size() << endl;
  for (int i = 0; i < 10; i++)
    l->pushBack(i);
  cout << "List back: " << l->back() << endl;
  for (auto n = l->begin(); n != l->end(); n = n->next())
    cout << n->value() << " ";
  cout << endl;
  cout << "List size: " << l->size() << endl;

  /* pop tests */
  while (!l->empty()) {
    cout << "List front: " << l->front() << endl;
    cout << "List back: " << l->back() << endl;
    cout << "List size: " << l->size() << endl;
    l->popBack();
    l->popFront();
  }
  try {
    l->popBack();
  } catch (underflow u) {
    cout << "underflow caught" << endl;
  }
  try {
    l->popFront();
  } catch (underflow u) {
    cout << "underflow caught" << endl;
  }
  cout << "List size: " << l->size() << endl;
  cout << "List empty: " << l->empty() << endl;

  delete l;
  return 0;
}