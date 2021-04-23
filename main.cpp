#include "data_struct/list.hpp"
#include <cstdlib>

using namespace std;

int main() {
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

  return EXIT_SUCCESS;
}
