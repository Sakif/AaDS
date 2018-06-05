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

	template <typename T>
	friend std::ostream &operator<<(std::ostream &, Resizable_deque<T> const &);
};

template <typename Type>
Resizable_deque<Type>::Resizable_deque(int n) {}

template <typename Type>
Resizable_deque<Type>::Resizable_deque(Resizable_deque const &deque) {}

template <typename Type>
Resizable_deque<Type>::Resizable_deque(Resizable_deque &&deque) {}

template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {}

template <typename Type>
int Resizable_deque<Type>::size() const {
	return 0;
}

template <typename Type>
int Resizable_deque<Type>::capacity() const {
	return 0;
}

template <typename Type>
bool Resizable_deque<Type>::empty() const {
	return 0;
}

template <typename Type>
Type Resizable_deque<Type>::front() const {
	return Type();
}

template <typename Type>
Type Resizable_deque<Type>::back() const {
	return Type();
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
void Resizable_deque<Type>::push_front(Type const &obj) {}

template <typename Type>
void Resizable_deque<Type>::push_back(Type const &obj) {}

template <typename Type>
void Resizable_deque<Type>::pop_front() {}

template <typename Type>
void Resizable_deque<Type>::pop_back() {}

template <typename Type>
void Resizable_deque<Type>::clear() {}

template <typename T>
std::ostream &operator<<(std::ostream &out, Resizable_deque<T> const &list) {
	out << "not yet implemented";
	return out;
}

#endif
