#include "double_sentinel_list.hpp"
#include "test.hpp"
#include <cassert>

using namespace std;

void
test_list_int()
{
  double_sentinel_list<int> list;
  assert(list.size() == 0);
  assert(list.empty());

  try
  {
    list.front();
  }
  catch (underflow_error e)
  {
    cout << e.what() << endl;
  }

  try
  {
    list.back();
  }
  catch (underflow_error e)
  {
    cout << e.what() << endl;
  }

  try
  {
    list.pop_back();
  }
  catch (underflow_error e)
  {
    cout << e.what() << endl;
  }

  try
  {
    list.pop_front();
  }
  catch (underflow_error e)
  {
    cout << e.what() << endl;
  }

  list.push_front(50);
  assert(list.front() == 50);
  assert(!list.empty());
  assert(list.size() == 1);
  assert(list.back() == 50);

  list.push_front(5);
  assert(list.front() == 5);
  assert(list.back() == 50);

  list.push_back(500);
  assert(list.front() == 5);
  assert(list.size() == 3);
  assert(list.back() == 500);

  assert(list.count(500) == 1);

  for (auto i = 0; i < 5; i++)
  {
    list.push_back(17);
    list.push_front(17);
    list.push_back(19);
  }
  auto list2 = double_sentinel_list<int>(list);

  assert(list.count(17) == 10);
  assert(list.count(7) == 0);
  assert(list.size() == 18);

  auto node = list.find(5);
  assert(node->value() == 5);
  assert(node->next()->value() == 50);
  assert(node->previous()->value() == 17);
  node = list.find(4);
  assert(node == list.end());

  while (list.front() != 5)
  {
    list.pop_front();
  }
  assert(list.size() == 13);
  assert(list.erase(17) == 5);
  assert(list.count(19) == 5);
  assert(list.back() == 19);
  cout << list << endl;
  cout << list2 << endl;
  list2 = list;
  list.pop_back();
  cout << list2 << endl;
}
