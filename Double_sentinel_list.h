#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
public:
  class Double_node {
  public:
	Double_node(Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr);

	// Accessors
	Type value() const;
	Double_node *previous() const;
	Double_node *next() const;

	// Members
	Type node_value;
	Double_node *previous_node;
	Double_node *next_node;
  };

  Double_sentinel_list();

  // Accessors
  int size() const;
  bool empty() const;
  Type front() const;

private:
  Double_node *list_head;
  Double_node *list_tail;
  int list_size;
};

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(Type const &nv, Double_node *pn, Double_node *nn) {
  node_value = nv;
  previous_node = pn;
  next_node = nn;
  // debugging:
  std::cout << "Node created\n";
  //*/
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

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list() {
  list_head = new Double_sentinel_list<Type>::Double_node(0, nullptr, nullptr);
  list_tail = new Double_sentinel_list<Type>::Double_node(0, list_head, nullptr);
  list_head->next_node = list_tail;
  list_size = 0;
  // debugging:
  std::cout << "List created\n";
  //*/
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
  if(empty()) throw underflow();
  Type item = Type();
  return item;
}

#endif
