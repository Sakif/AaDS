#include "HashTable.hpp"

using namespace std;

int main() {
	auto hash = new Hash_Table<int>();
	cout << "Size: " << hash->size() << endl;
	cout << "Empty: " << hash->empty() << endl;
	cout << "Capacity: " << hash->capacity() << endl;
	cout << "Load Factor: " << hash->load_factor() << endl;
	cout << "Member 394: " << hash->member(394) << endl;
	hash->insert(394);
	cout << "Member 394: " << hash->member(394) << endl;
	cout << "Member -3: " << hash->member(-3) << endl;
	hash->insert(-3);
	cout << "Member -3: " << hash->member(-3) << endl;
	cout << "Bin 29: " << hash->bin(29) << endl;
	cout << "Bin 10: " << hash->bin(10) << endl;
	cout << "Bin 1: " << hash->bin(1) << endl;
	cout << "Load Factor: " << hash->load_factor() << endl;
	cout << "Erace 1: " << hash->erace(3) << endl;
	cout << "Erace 394: " << hash->erace(394) << endl;
	cout << "Load Factor: " << hash->load_factor() << endl;
	auto ht = new Hash_Table<int>(10);
	for (int i = 93251234; i < 93251534; i += 9382)
		ht->insert(i);
	ht->print();
	return 0;
}
