#include "doubleSentinelList.hpp"
#include <iostream>

using namespace std;

int main() {
  cout << "" << endl;
  cout << "Double Sentinels List Test" << endl;
  doubleSentinelList<int> list;
  cout << "Construction Successful" << endl;
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
  return 0;
}
