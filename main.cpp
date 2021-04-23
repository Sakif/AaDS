#include "data_struct/list.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
  auto l = AaDS::double_list<int>();

  cout<<"List size: "<<l.size()<<endl;

  return EXIT_SUCCESS;
}
