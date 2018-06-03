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

	template <typename T>
	friend std::ostream &operator<<(std::ostream &, Double_sentinel_list<T> const &);
};

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list() {
	/* The constructor creates two instances of a Double_node<Type> (called the sentinels). The head and tail pointers are set to point to one of the sentinels, each. The values stored in these nodes is not important, you can use the default value or whatever values you want. The previous and next pointers of the head sentinel should be nullptr and the address of the tail sentinel, respectively. The previous and next pointers of the tail sentinel should be address of the head sentinel and nullptr, respectively. The node count is set to 0. (O(1)) */
	list_head = new Double_sentinel_list<Type>::Double_node(0, nullptr, nullptr);
	list_tail = new Double_sentinel_list<Type>::Double_node(0, list_head, nullptr);
	list_head->next_node = list_tail;
	list_size = 0;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list(Double_sentinel_list<Type> const &list) {
	/* The copy constructor must create a new doubly linked list with a copy of all of the nodes within the linked list pass as the argument list with the values stored in the same order. The linked list passed as an argument may not be changed. Once a copy is made, any change to the original linked list must not affect the copy. (O(n)) */
	list_head = new Double_sentinel_list<Type>::Double_node(0, nullptr, nullptr);
	list_tail = new Double_sentinel_list<Type>::Double_node(0, list_head, nullptr);
	list_head->next_node = list_tail;
	list_size = 0;
	for (auto node = list.begin(); node != end(); node = node->next())
		push_back(node->value());
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list(Double_sentinel_list<Type> &&list) {
	/* The move constructor must create a new doubly linked list with all the nodes found within the linked list passed as an argument list with the values stored in the same order. It is assumed that the destructor will immediately be called on the argument linked list as soon as this constructor finishes, so all the nodes in the argument linked list can be used in this newly created linked list. The argument linked list should be updated to one that is empty. (This is most easily done by initializing this linked list as an empty linked list and then calling swap.) */
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	/* The destructor must delete each of the nodes in the list including the sentinels. (O(n)) */
	while (!empty())
		pop_front();
	delete list_head;
	delete list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	/* Returns the number of items in the list. (O(1)) */
	return list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	/* Returns true if the list is empty, false otherwise. (O(1)) */
	return size() == 0;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	/* Retrieves the object stored in the node pointed to by the next pointer of the head sentinel. This function throws a underflow if the list is empty. (O(1)) */
	if (empty())
		throw underflow();
	else
		return begin()->value();
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	/* Retrieves the object stored in the node pointed to by the previous pointer of the tail sentinel. This function throws a underflow if the list is empty. (O(1)) */
	if (empty())
		throw underflow();
	else
		return rbegin()->value();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	/* Returns the address stored by the next pointer of the head sentinel node. (O(1)) */
	return rend()->next();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	/* Returns the address of the tail sentinel node. (O(1)) */
	return list_tail;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	/* Returns the address stored by the previous pointer of the tail sentinel node. (O(1)) */
	return rend()->previous();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	/* Returns the address of the head sentinel node. (O(1)) */
	return list_head;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find(Type const &obj) const {
	/* Returns the address of the first node in the linked list storing a value equal to the argument; if none is found, return end(). (O(n)) */
	for (auto node = begin(); node != end(); node = node->next()) {
		if (node->value() == obj)
			return node;
	}
	return end();
}

template <typename Type>
int Double_sentinel_list<Type>::count(Type const &obj) const {
	/* Returns the number of nodes in the linked list storing a value equal to the argument. (O(n)) */
	int count = 0;
	for (auto node = begin(); node != end(); node = node->next()) {
		if (node->value() == obj)
			count++;
	}
	return count;
}

template <typename Type>
void Double_sentinel_list<Type>::swap(Double_sentinel_list<Type> &list) {
	/* The swap function swaps all the member variables of this linked list with those of the argument list. (O(1)) */
	std::swap(list_head, list.list_head);
	std::swap(list_tail, list.list_tail);
	std::swap(list_size, list.list_size);
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=(Double_sentinel_list<Type> rhs) {
	/* The assignment operator makes a copy of the argument (the right-hand side of the assignment) and then swaps the member variables of this node doubly linked sentinel list those of the copy. (O(nlhs + nrhs)) */
	swap(rhs);
	return *this;
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=(Double_sentinel_list<Type> &&rhs) {
	/* The move operator moves the nodes in the argument (the right-hand side of the assignment) linked list to this linked list, changing the argument linked list into an empty list. (O(1)) */
	swap(rhs);
	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front(Type const &obj) {
	/* Creates a new Double_node<Type> storing the argument new_value, the next pointer of which is set to the next pointer of the sentinel and the previous pointer is set to point to the sentinel. The next pointer of the sentinel and the previous pointer of what was the first node are set to this new node. (O(1)) */
	auto node = new Double_node(obj, rend(), begin());
	begin()->previous_node = node;
	rend()->next_node = node;
	list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back(Type const &obj) {
	/* Similar to push_front, this places a new node at the back of the list storing the argument new_value. (O(1)) */
	auto node = new Double_node(obj, rbegin(), end());
	rbegin()->next_node = node;
	end()->previous_node = node;
	list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
	/* Delete the first non-sentinel node at the front of the linked list and update the previous and next pointers of any other node (including possibly the sentinels) within the list as necessary. Throw an underflow exception if the list is empty. (O(1)) */
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
	/* Similar to pop_front, delete the last non-sentinel node in the list. This function throws a underflow if the list is empty. (O(1)) */
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
	/* Delete all the nodes in the linked list that have a value equal to the argument value (use == to to test for equality with the retrieved element). Update the previous and next pointers of any other node (including possibly the sentinels) within the list. Return the number of nodes that were deleted. (O(n)) */
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
	/* This constructor takes three arguments: a constant reference to an Type (by default, a new instance of the class Type) and two pointers to a Double_node (each by default nullptr). These are assigned to the member variables, respectively. (O(1)) */
	node_value = nv;
	previous_node = pn;
	next_node = nn;
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	/* Returns the value of the node. (O(1)) */
	return node_value;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	/* Returns the previous pointer. (O(1)) */
	return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	/* Returns the next pointer. (O(1)) */
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
