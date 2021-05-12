#include "data_struct/deque.hpp"
#include "data_struct/list.hpp"
#include <cstdlib>

using namespace std;

int main() {
  auto queue = AaDS::deque<int>();
  auto l = AaDS::double_list<int>();

  cout << "List size: " << l.size() << endl
       << "List empty: " << l.empty() << endl;
  try {
    l.front();
  } catch (underflow_error a) {
    cout << "Underflow front\n";
  }

  try {
    l.back();
  } catch (underflow_error a) {
    cout << "Underflow back\n";
  }

  l.push_back(9);
  l.push_back(82);
  l.push_front(34);
  cout << l << endl;

  cout << "List size: " << l.size() << endl
       << "List empty: " << l.empty() << endl
       << "Front: " << l.front() << endl
       << "Back: " << l.back() << endl;

#define size 6
  auto ifront = 3;
  for (auto i = 0; i < size; i++) {
    cout << ifront << " ";
    if (--ifront < 0) {
      ifront += size;
    }
  }

  return EXIT_SUCCESS;
}
