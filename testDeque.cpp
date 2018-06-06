#include "Resizable_deque.hpp"

using namespace std;

int main() {
	//
	auto deque = Resizable_deque<int>(5);
	cout << "Empty: " << deque.empty() << endl;
	cout << "Size: " << deque.size() << endl;
	cout << "Capicity: " << deque.capacity() << endl;
	try {
		deque.front();
	} catch (underflow) {
		cout << "Underflow caught!\n";
	}
	try {
		deque.back();
	} catch (underflow) {
		cout << "Underflow caught!\n";
	}
	deque.push_front(7);
	deque.push_front(8);
	cout << "Front: " << deque.front() << endl;
	cout << "Empty: " << deque.empty() << endl;
	cout << "Size: " << deque.size() << endl;
	deque.clear();
	cout << deque << endl;
	cout << "Empty: " << deque.empty() << endl;
	cout << "Size: " << deque.size() << endl;
	cout << "Capicity: " << deque.capacity() << endl;
	try {
		deque.front();
	} catch (underflow) {
		cout << "Underflow caught!\n";
	}
	try {
		deque.back();
	} catch (underflow) {
		cout << "Underflow caught!\n";
	} //*/
	return 0;
}
