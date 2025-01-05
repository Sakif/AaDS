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

  for (auto i = 0U; i < 5; i++)
  {
    list.push_back(17);
    list.push_front(17);
  }

  assert(list.count(17) == 10);
  assert(list.count(7) == 0);
  assert(list.size() == 13);

  while (list.front() != 5)
  {
    list.pop_front();
  }
  assert(list.size() == 8);

  while (list.back() != 500)
  {
    list.pop_back();
  }

  cout << "\nList front to back:\n";
  for (auto n = list.begin(); n != list.end(); n = n->next())
  {
    cout << n->value() << endl;
  }

  cout << "\nList back to front:\n";
  for (auto n = list.rbegin(); n != list.rend(); n = n->previous())
  {
    cout << n->value() << endl;
  }
}
