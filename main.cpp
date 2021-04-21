#include "header/array.hpp"
#include <cstdlib>
#include <iostream>
#include <ostream>

using namespace std;

int main() {
  auto info = AaDS::array(30);

  for (auto i = 0U; i < info.capacity(); i++) {
    auto r = rand() % 100;
    info.append(r);
  }

  for (auto i = 0U; i < info.size(); i++) {
    cout << info[i] << ", ";
  }

  cout << endl
       << "Sum: " << info.sum() << endl
       << "Average: " << info.average() << endl
       << "Variance: " << info.variance() << endl
       << "Std Dev: " << info.std_dev() << endl;

  AaDS::array a(3), b(5);
  a.append(54);
  a.append(25);
  a.append(37);
  b.append(92);
  b.append(82);
  a.swap(b);

  cout << "a size: " << a.size() << endl
       << "a capacity: " << a.capacity() << endl
       << "b size: " << b.size() << endl
       << "b capacity: " << b.capacity() << endl;

  return EXIT_SUCCESS;
}
