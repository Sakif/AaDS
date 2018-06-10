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
	cout << "Back: " << deque.back() << endl;
	cout << "Empty: " << deque.empty() << endl;
	cout << "Size: " << deque.size() << endl;
	deque.clear();
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
	try {
		deque.pop_back();
	} catch (underflow) {
		cout << "Underflow caught!\n";
	}
	try {
		deque.pop_front();
	} catch (underflow) {
		cout << "Underflow caught!\n";
	}
	for (int i = 0; i < 16; i++)
		deque.push_back(i);
	for (int i = 0; i < 8; i++)
		deque.push_front(99);
	for (int i = 0; i < 8; i++)
		deque.push_back(88);
	cout << "Back: " << deque.back() << endl;
	cout << "Front: " << deque.front() << endl;
	deque.push_back(55);
	deque.push_front(55);
	deque.pop_back();
	deque.pop_front();
	cout << deque << endl;
	//*/
	return 0;
}
