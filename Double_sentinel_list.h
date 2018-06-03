#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include "Exception.h"
#include <iostream>

template <typename Type>
class Double_sentinel_list {
public:
	class Double_node {
	public:
		Double_node(Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr);

		Type value() const;
		Double_node *previous() const;
		Double_node *next() const;

		Type node_value;
		Double_node *previous_node;
		Double_node *next_node;
	};

	Double_sentinel_list();
	Double_sentinel_list(Double_sentinel_list const &);
	Double_sentinel_list(Double_sentinel_list &&);
	~Double_sentinel_list();

	// Accessors
	int size() const;
	bool empty() const;
	Type front() const;
	Type back() const;
	Double_node *begin() const;
	Double_node *end() const;
	Double_node *rbegin() const;
	Double_node *rend() const;
	Double_node *find(Type const &) const;
	int count(Type const &) const;

	// Mutators
	void swap(Double_sentinel_list &);
	Double_sentinel_list &operator=(Double_sentinel_list);
	Double_sentinel_list &operator=(Double_sentinel_list &&);
	void push_front(Type const &);
	void push_back(Type const &);
	void pop_front();
	void pop_back();
	int erase(Type const &);

private:
	Double_node *list_head;
	Double_node *list_tail;
	int list_size;

	// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<(std::ostream &, Double_sentinel_list<T> const &);
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list() {
	list_head = new Double_sentinel_list<Type>::Double_node(0, nullptr, nullptr);
	list_tail = new Double_sentinel_list<Type>::Double_node(0, list_head, nullptr);
	list_head->next_node = list_tail;
	list_size = 0;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list(Double_sentinel_list<Type> const &list) {}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list(Double_sentinel_list<Type> &&list) {}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	while (!empty())
		pop_front();
	delete list_head;
	delete list_tail;
	delete list_size;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	return list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	return size() == 0;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	if (empty())
		throw underflow();
	else
		return begin()->value();
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	if (empty())
		throw underflow();
	else
		return rbegin()->value();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	return rend()->next();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	return list_tail;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	return rend()->previous();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	return list_head;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find(Type const &obj) const {
	for (auto node = begin(); node != end(); node = node->next()) {
		if (node->value() == obj)
			return node;
	}
	return end();
}

template <typename Type>
int Double_sentinel_list<Type>::count(Type const &obj) const {
	int count = 0;
	for (auto node = begin(); node != end(); node = node->next()) {
		if (node->value() == obj)
			count++;
	}
	return count;
}

template <typename Type>
void Double_sentinel_list<Type>::swap(Double_sentinel_list<Type> &list) {
	std::swap(list_head, list.list_head);
	std::swap(list_tail, list.list_tail);
	std::swap(list_size, list.list_size);
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=(Double_sentinel_list<Type> rhs) {
	swap(rhs);
	return *this;
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=(Double_sentinel_list<Type> &&rhs) {
	swap(rhs);
	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front(Type const &obj) {
	auto node = new Double_node(obj, rend(), begin());
	begin()->previous_node = node;
	rend()->next_node = node;
	list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back(Type const &obj) {
	auto node = new Double_node(obj, rbegin(), end());
	rbegin()->next_node = node;
	end()->previous_node = node;
	list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
	if (empty())
		throw underflow();
	else {
		auto node = begin();
		rend()->next_node = node->next();
		node->next()->previous_node = rend();
		list_size--;
		delete node;
	}
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
	if (empty())
		throw underflow();
	else {
		auto node = rbegin();
		end()->previous_node = node->previous();
		node->previous()->next_node = end();
		list_size--;
		delete node;
	}
}

template <typename Type>
int Double_sentinel_list<Type>::erase(Type const &obj) {
	int count = 0;
	for (auto node = rend(); node != end(); node = node->next()) {
		if (node->next()->value() == obj) {
			count++;
			list_size--;
			auto temp = node->next();
			node->next_node = temp->next();
			temp->next()->previous_node = node;
			delete temp;
		}
	}
	return count;
}

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(Type const &nv, Double_node *pn, Double_node *nn) {
	node_value = nv;
	previous_node = pn;
	next_node = nn;
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	return node_value;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	return next_node;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, Double_sentinel_list<T> const &list) {
	out << "head";
	for (auto ptr = list.rend(); ptr != nullptr; ptr = ptr->next()) {
		if (ptr == list.rend() || ptr == list.end())
			out << "->S";
		else
			out << "->" << ptr->value();
	}
	out << "->0\ntail";
	for (auto ptr = list.end(); ptr != nullptr; ptr = ptr->previous()) {
		if (ptr == list.rend() || ptr == list.end())
			out << "->S";
		else
			out << "->" << ptr->value();
	}
	out << "->0";
	return out;
}

#endif
