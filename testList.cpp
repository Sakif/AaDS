#include "Double_sentinel_list.hpp"

using namespace std;

int main() {
	auto list = Double_sentinel_list<int>();
	cout << "List size: " << list.size() << endl;
	cout << "List empty: " << list.empty() << endl;
	try {
		list.front();
	} catch (underflow) {
		cout << "Underflow Caught!\n";
	}
	try {
		list.back();
	} catch (underflow) {
		cout << "Underflow Caught!\n";
	}
	try {
		list.pop_back();
	} catch (underflow) {
		cout << "Underflow Caught!\n";
	}
	try {
		list.pop_front();
	} catch (underflow) {
		cout << "Underflow Caught!\n";
	}
	list.push_front(7);
	list.push_back(12);
	cout << "List size: " << list.size() << endl;
	cout << "List empty: " << list.empty() << endl;
	return 0;
}
