#include "HashTable.hpp"

using namespace std;

int main() {
	auto hash = Hash_Table<int>();
	cout << "Size: " << hash.size() << endl;
	cout << "Empty: " << hash.empty() << endl;
	cout << "Capacity: " << hash.capacity() << endl;
	cout << "Load Factor: " << hash.load_factor() << endl;
	cout << "Member 394: " << hash.member(394) << endl;
	hash.insert(394);
	cout << "Member 394: " << hash.member(394) << endl;
	cout << "Member -3: " << hash.member(-3) << endl;
	hash.insert(-3);
	cout << "Member -3: " << hash.member(-3) << endl;
	cout << "Bin 29: " << hash.bin(29) << endl;
	cout << "Bin 10: " << hash.bin(10) << endl;
	cout << "Bin 1: " << hash.bin(1) << endl;
	return 0;
}
