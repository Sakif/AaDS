#include "Exception.h"
#include "ece250.h"
#include <iostream>

enum bin_state_t {
	UNOCCUPIED,
	OCCUPIED,
	ERASED
};

template <typename Type>
class Hash_Table {
private:
	int count;
	int power;
	int array_size;
	int mask;
	Type *array;
	bin_state_t *occupied;
	int hash(Type const &) const;

public:
	Hash_Table(int = 5);
	int size() const;
	int capacity() const;
	double load_factor() const;
	bool empty() const;
	bool member(Type const &) const;
	Type bin(int n) const;
	void print() const;

	void insert(Type const &);
	bool erace(Type const &);
	void clear();
};

template <typename Type>
Hash_Table<Type>::Hash_Table(int m) {
	count = 0;
	power = m;
	array_size = 1 << power;
	mask = array_size - 1;
	array = new Type[array_size];
	occupied = new bin_state_t[array_size];
	for (int i = 0; i < array_size; i++)
		occupied[i] = UNOCCUPIED;
}

template <typename Type>
void Hash_Table<Type>::clear() {
	for (int i = 0; i < array_size; i++)
		occupied[i] = UNOCCUPIED;
	count = 0;
}

template <typename Type>
int Hash_Table<Type>::size() const {
	return count;
}

template <typename Type>
int Hash_Table<Type>::capacity() const {
	return array_size;
}

template <typename Type>
double Hash_Table<Type>::load_factor() const {
	return static_cast<double>(size()) / static_cast<double>(capacity());
}

template <typename Type>
bool Hash_Table<Type>::empty() const {
	return size() == 0;
}

template <typename Type>
bool Hash_Table<Type>::member(const Type &obj) const {
	int i = static_cast<int>(obj);
	i %= capacity();
	if (i < 0)
		i += capacity();
	return occupied[i] == OCCUPIED;
}

template <typename Type>
Type Hash_Table<Type>::bin(int n) const {
	if (occupied[n] == OCCUPIED)
		return array[n];
	else
		return 0;
}

template <typename Type>
bool Hash_Table<Type>::erace(const Type &obj) {
	int i = static_cast<int>(obj);
	i %= capacity();
	if (i < 0)
		i += capacity();
	if (occupied[i] != OCCUPIED)
		return false;
	else {
		occupied[i] = ERASED;
		count--;
	}
}

template <typename Type>
void Hash_Table<Type>::insert(const Type &obj) {
	if (size() >= capacity())
		throw overflow();
	int i = static_cast<int>(obj);
	i %= capacity();
	if (i < 0)
		i += capacity();
	if (occupied[i] != OCCUPIED) {
		array[i] = obj;
		occupied[i] = OCCUPIED;
		count++;
	}
}

template <typename Type>
void Hash_Table<Type>::print() const {
	for (int i = 0; i < capacity(); i++) {
		if (occupied[i] == OCCUPIED)
			std::cout << array[i] << ", ";
		else if (occupied[i] == ERASED)
			std::cout << "ERASED, ";
		else
			std::cout << "UNOCCUPIED, ";
	}
}
