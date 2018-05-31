#include "Double_sentinel_list.h"

using namespace std;

int main() {
  cout << "Begin Test\n";
  Double_sentinel_list<int> *list = new Double_sentinel_list<int>();
  cout << "List Size: " << list->size() << endl;
  cout << "List is empty: " << list->empty() << endl;
  try {list->front();} catch(underflow) {cout << "Underflow caught\n";}
  cout << "End Test\n";
  return 0;
}
