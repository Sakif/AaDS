#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#include "Exception.h"
#include <iostream>

template <typename Type>
class Resizable_deque {
public:
	Resizable_deque(int = 16);
	Resizable_deque(Resizable_deque const &);
	Resizable_deque(Resizable_deque &&);
	~Resizable_deque();

	Type front() const;
	Type back() const;
	int size() const;
	bool empty() const;
	int capacity() const;

	void swap(Resizable_deque &);
	Resizable_deque &operator=(Resizable_deque const &);
	Resizable_deque &operator=(Resizable_deque &&);
	void push_front(Type const &);
	void push_back(Type const &);
	void pop_front();
	void pop_back();
	void clear();

private:
	int ifront;
	int iback;
	int deque_size;
	int initial_array_capacity;
	int array_capacity;
	Type *array;

	void doubleSize();
	void halfSize();

	template <typename T>
	friend std::ostream &operator<<(std::ostream &, Resizable_deque<T> const &);
};

// Constructors
template <typename Type>
Resizable_deque<Type>::Resizable_deque(int n) { /* The constructor takes as an argument the initial capacity of the array and allocates memory for that array. The initial array capacity must be 16 or more, with a default capacity of 16. If the user passes a value less than 16, use 16. Other member variables are assigned as appropriate. */
	if (n < 16)
		n = 16;
	deque_size = 0;
	initial_array_capacity = n;
	array_capacity = initial_array_capacity;
	array = new Type[array_capacity];
	ifront = 0;
	iback = 0;
}

// Copy constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque(Resizable_deque const &deque) {}

// Move constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque(Resizable_deque &&deque) {}

// Destructor
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() { /* The destructor deletes the memory allocated for the array. */
	delete array;
}

template <typename Type>
int Resizable_deque<Type>::size() const { /* Returns the number of elements currently stored in the deque. (O(1)) */
	return deque_size;
}

template <typename Type>
int Resizable_deque<Type>::capacity() const { /* Returns the current capacity of the array. (O(1)) */
	return array_capacity;
}

template <typename Type>
bool Resizable_deque<Type>::empty() const { /* Returns true if the deque is empty, false otherwise. (O(1)) */
	return size() == 0;
}

template <typename Type>
Type Resizable_deque<Type>::front() const { /* Return the object at the front of the deque. It may throw a underflow exception. (O(1)) */
	if (empty())
		throw underflow();
	else {
		return array[ifront];
	}
}

template <typename Type>
Type Resizable_deque<Type>::back() const { /* Return the object at the back of the deque. It may throw a underflow exception. (O(1)) */
	if (empty())
		throw underflow();
	else {
		return array[iback];
	}
}

template <typename Type>
void Resizable_deque<Type>::swap(Resizable_deque<Type> &deque) {}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=(Resizable_deque<Type> const &rhs) {
	Resizable_deque<Type> copy(rhs);
	swap(copy);
	return *this;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=(Resizable_deque<Type> &&rhs) {
	swap(rhs);
	return *this;
}

template <typename Type>
void Resizable_deque<Type>::push_front(Type const &obj) { /* Insert the new element at the front of the deque. If before the element is placed into the deque, the array is filled, the capacity of the array is doubled. (O(1) on average) */
	deque_size++;
	if (size() > capacity())
		doubleSize();
	size() == 1 ? ifront = 0 : ifront++;
	ifront %= capacity();
	array[ifront] = obj;
}

template <typename Type>
void Resizable_deque<Type>::push_back(Type const &obj) { /* Insert the new element at the back of the deque. If before the element is placed into the deque, the array is filled, the capacity of the array is doubled. (O(1) on average) */
	deque_size++;
	if (size() > capacity())
		doubleSize();
	iback--;
	if (iback < 0)
		iback += capacity();
	array[iback] = obj;
}

template <typename Type>
void Resizable_deque<Type>::doubleSize() {
	auto ar = new Type[capacity() * 2];
	for (int i = 0, n = iback; i < capacity(); i++, n++) {
		n %= capacity();
		ar[i] = array[n];
	}
	iback = 0;
	ifront = capacity() - 1;
	array_capacity *= 2;
}

template <typename Type>
void Resizable_deque<Type>::pop_front() { /* Removes the element at the front of the deque. If, after the element is removed, the array is 1/4 full or less and the array capacity is greater than the initial capacity, the capacity of the array is halved. This may throw a underflow exception. (O(1) on average) */
	if (empty())
		throw underflow();
	else {
		deque_size--;
		if (size() > initial_array_capacity && size() < capacity() / 4)
			halfSize();
		array[ifront] = Type();
		ifront--;
		if (ifront < 0)
			ifront += capacity();
	}
}

template <typename Type>
void Resizable_deque<Type>::pop_back() { /* Removes the element at the back of the deque. If, after the element is removed, the array is 1/4 full or less and the array capacity is greater than the initial capacity, the capacity of the array is halved. This may throw a underflow exception. (O(1) on average) */
	if (empty())
		throw underflow();
	else {
		deque_size--;
		if (size() > initial_array_capacity && size() < capacity() / 4)
			halfSize();
		array[iback] = Type();
		iback++;
		iback %= capacity();
	}
}

template <typename Type>
void Resizable_deque<Type>::halfSize() {
	auto ar = new Type[capacity() / 2];
	for (int i = 0, n = iback; i < capacity(); i++, n++) {
		n %= capacity() / 2;
		ar[i] = array[n];
	}
	iback = 0;
	ifront = capacity() / 2 - 1;
	array_capacity /= 2;
}

template <typename Type>
void Resizable_deque<Type>::clear() {
	/* Empties the deque by resetting the member variables. The array is resized to the initial capacity. (O(1)) */
	deque_size = 0;
	array_capacity = initial_array_capacity;
	ifront = 0;
	iback = 0;
	auto temp = new Type[array_capacity];
	array = temp;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, Resizable_deque<T> const &list) {
	for (int i = 0; i < list.array_capacity; i++)
		out << list.array[i] << ", ";
	return out;
}

#endif