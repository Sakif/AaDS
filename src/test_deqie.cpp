#include "dynamic_deque.hpp"
#include "test.hpp"
#include <cassert>
#include <exception>

using namespace std;

void
test_deque_int()
{
  dynamic_deque<int> queue(10);
  assert(queue.capacity() == 10);
  assert(queue.size() == 0);
  assert(queue.empty());

  try
  {
    queue.front();
  }
  catch (const exception &e)
  {
    cout << e.what() << endl;
  }
}
