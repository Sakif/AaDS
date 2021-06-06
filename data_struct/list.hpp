/*
Author: Sakif Fahmid Zaman

Description

This class stores a finite list of n (zero or more) elements stored in doubly
linked nodes. The following are properties of this class:
+ If there are zero elements in the list, the list is said to be empty.
+ Each element is stored in an instance of the Double_node<Type> class.
+ At all times, the head and tail pointers store the addresses of the head and
  tail sentinel nodes, respectively.
+ The previous pointer of the head sentinel always points to nullptr.
+ The next pointer of the tail sentinel always points to nullptr.
+ If the list is empty, the next pointer of the head sentinel node is assigned
  the address of the tail sentinel; otherwise, the next pointer of the head
  sentinel node is assigned the address of the first node in the linked list
  (the front node).
+ If the list is empty, the previous pointer of the tail sentinel node is
  assigned the address of the head sentinel; otherwise, the previous pointer of
  the tail sentinel node is assigned the address of the last node in the linked
  list (the back node).
+ The next pointer of the kth node (1 ≤ k < n) stores the address of the
  (k + 1)st node, the next pointer of the nth is assigned to the address of the
  tail sentinel.
+ The previous pointer of the kth node (1 < k ≤ n) stores the address of the
  (k − 1)st node, and the previous pointer of the first node is assigned the
  address of the head sentinel.

A nested class which stores an object, a pointer to the next node in a linked
list, and a pointer to the previous node in the linked list.
*/
#pragma once
#include <iostream>
#include <stdexcept>

#ifndef LIST_HPP
#define LIST_HPP

namespace AaDS {

template <typename type>
class double_list {
public:
  class node {
  private:
    type element;
    node *next_node;
    node *previous_node;

  public:
    /* constructor */
    node(type const & = type(), node * = nullptr, node * = nullptr);

    /* accessor */
    type value() const;
    node *previous() const;
    node *next() const;

    /* mutator */
    void set(type const & = type());

    /* to allow double_list access to private members */
    friend class double_list<type>;
  };

  /* constructior */
  double_list();
  double_list(double_list const &);
  ~double_list();

  /* accessors */
  unsigned size() const;
  bool empty() const;
  type front() const;
  type back() const;
  unsigned count(type const &) const;

  node *begin() const;
  node *end() const;
  node *rbegin() const;
  node *rend() const;
  node *find(type const &) const;

  /* mutator */
  void push_front(type const &);
  void push_back(type const &);
  type pop_front();
  type pop_back();

  unsigned erase(type const &);
  void swap(double_list &);

  /* assignment operator */
  double_list &operator=(double_list);
  /* move operator */
  double_list &operator=(double_list &&);

private:
  node *list_head;
  node *list_tail;
  unsigned list_size;

  template <typename t>
  friend std::ostream &operator<<(std::ostream &, double_list<t> const &);
};

/*
This constructor takes three arguments: a constant reference to an Type (by
default, a new instance of the class Type) and two pointers to a Double_node
(each by default nullptr). These are assigned to the member variables,
respectively. O(1)
*/
template <typename t>
double_list<t>::node::node(t const &obj, node *pn, node *nn)
    : element(obj), next_node(nn), previous_node(pn) {}

/* Returns the next pointer. O(1) */
template <typename t>
typename double_list<t>::node *double_list<t>::node::next() const {
  return next_node;
}

/* Returns the previous pointer. O(1) */
template <typename t>
typename double_list<t>::node *double_list<t>::node::previous() const {
  return previous_node;
}

/* Returns the value of the node. O(1) */
template <typename t>
t double_list<t>::node::value() const {
  return element;
}

/* changes the value of the node */
template <typename t>
void double_list<t>::node::set(const t &v) {
  element = v;
}

/*
The constructor creates two instances of a Double_node<Type> (called the
sentinels). The head and tail pointers are set to point to one of the sentinels,
each. The values stored in these nodes is not important, you can use the default
value or whatever values you want. The previous and next pointers of the head
sentinel should be nullptr and the address of the tail sentinel, respectively.
The previous and next pointers of the tail sentinel should be address of the
head sentinel and nullptr, respectively. The node count is set to 0. O(1)
*/
template <typename t>
double_list<t>::double_list()
    : list_head(new node()), list_tail(new node(t(), list_head)), list_size(0) {
  list_head->next_node = list_tail;
}

/*
The copy constructor must create a new doubly linked list with a copy of all of
the nodes within the linked list pass as the argument list with the values
stored in the same order. The linked list passed as an argument may not be
changed. Once a copy is made, any change to the original linked list must not
affect the copy. O(n)
*/
template <typename t>
double_list<t>::double_list(double_list const &l)
    : list_head(new node()), list_tail(new node(t(), list_head)),
      list_size(l.size()) {
  for (auto n = l.begin(); n != l.end(); n = n->next()) {
    push_back(n->value());
  }
}

/*
The destructor must delete each of the nodes in the list including the
sentinels. O(n)
*/
template <typename t>
double_list<t>::~double_list() {
  while (!empty()) {
    pop_front();
  }
  delete list_head;
  delete list_tail;
}

/* Returns the number of items in the list. O(1) */
template <typename t>
unsigned double_list<t>::size() const {
  return list_size;
}

/* Returns true if the list is empty, false otherwise. O(1) */
template <typename t>
bool double_list<t>::empty() const {
  return (size() == 0);
}

/*
Returns the number of nodes in the linked list storing a value equal to the
argument. O(n)
*/
template <typename t>
unsigned double_list<t>::count(const t &obj) const {
  auto obj_count = 0U;
  for (auto node = begin(); node != end(); node = node->next()) {
    if (node->value() == obj) {
      obj_count++;
    }
  }
  return obj_count;
}

/*
Retrieves the object stored in the node pointed to by the next pointer of the
head sentinel. This function throws a underflow if the list is empty. O(1)
*/
template <typename t>
t double_list<t>::front() const {
  if (empty()) {
    throw std::underflow_error("List is empty.");
  }
  return begin()->value();
}

/*
Retrieves the object stored in the node pointed to by the previous pointer of
the tail sentinel. This function throws a underflow if the list is empty. O(1)
*/
template <typename t>
t double_list<t>::back() const {
  if (empty()) {
    throw std::underflow_error("List is empty.");
  }
  return rbegin()->value();
}

/*
Returns the address stored by the next pointer of the head sentinel node. O(1)
*/
template <typename t>
typename double_list<t>::node *double_list<t>::begin() const {
  return list_head->next();
}

/* Returns the address of the tail sentinel node. O(1) */
template <typename t>
typename double_list<t>::node *double_list<t>::end() const {
  return list_tail;
}

/*
Returns the address stored by the previous pointer of the tail sentinel node.
O(1)
*/
template <typename t>
typename double_list<t>::node *double_list<t>::rbegin() const {
  return list_tail->previous();
}

/* Returns the address of the head sentinel node. O(1) */
template <typename t>
typename double_list<t>::node *double_list<t>::rend() const {
  return list_head;
}

/*
Returns the address of the first node in the linked list storing a value equal
to the argument; if none is found, return end(). O(n)
*/
template <typename t>
typename double_list<t>::node *double_list<t>::find(const t &obj) const {
  for (auto node = begin(); node != end(); node = node->next()) {
    if (node->value() == obj) {
      return node;
    }
  }
  return end();
}

/*
Creates a new Double_node<Type> storing the argument new_value, the next pointer
of which is set to the next pointer of the sentinel and the previous pointer is
set to point to the sentinel. The next pointer of the sentinel and the previous
pointer of what was the first node are set to this new node. O(1)
*/
template <typename t>
void double_list<t>::push_front(t const &obj) {
  auto new_node = new node(obj, rend(), begin());
  begin()->previous_node = new_node;
  rend()->next_node = new_node;
  list_size++;
}

/*
Similar to push_front, this places a new node at the back of the list storing
the argument new_value. O(1)
*/
template <typename t>
void double_list<t>::push_back(t const &obj) {
  auto new_node = new node(obj, rbegin(), end());
  rbegin()->next_node = new_node;
  end()->previous_node = new_node;
  list_size++;
}

/*
Delete the first non-sentinel node at the front of the linked list and update
the previous and next pointers of any other node (including possibly the
sentinels) within the list as necessary. Throw an underflow exception if the
list is empty. O(1)
*/
template <typename t>
t double_list<t>::pop_front() {
  auto value = front();
  auto node = begin();
  rend()->next_node = node->next();
  node->next()->previous_node = rend();
  list_size--;
  delete node;
  return value;
}

/*
Similar to pop_front, delete the last non-sentinel node in the list. This
function throws a underflow if the list is empty. O(1)
*/
template <typename t>
t double_list<t>::pop_back() {
  auto value = back();
  auto node = rbegin();
  end()->previous_node = node->previous();
  node->previous()->next_node = end();
  list_size--;
  delete node;
  return value;
}

/*
Delete all the nodes in the linked list that have a value equal to the argument
value (use == to to test for equality with the retrieved element). Update the
previous and next pointers of any other node (including possibly the sentinels)
within the list. Return the number of nodes that were deleted. O(n)
*/
template <typename t>
unsigned double_list<t>::erase(const t &obj) {
  auto count = 0U;
  for (auto n = begin(); n != end(); n = n->next()) {
    if (n->value() == obj) {
      auto to_delete = n;
      /* go to the node next to the one to be deleated */
      n = to_delete->next();
      /* then change the previous node link for that to the node before the one to be deleated */
      n->previous_node = to_delete->previous();
      /* go to the node before the one to be deleated */
      n = to_delete->previous();
      /* then change the next node link to the node after the one to be deleated */
      n->next_node = to_delete->next();
      /* delete the node */
      delete to_delete;
      /* inclease the counter */
      count++;
    }
  }
  return count;
}

template <typename t>
void double_list<t>::swap(double_list<t> &list) {
  std::swap(list_head, list.list_head);
  std::swap(list_tail, list.list_tail);
  std::swap(list_size, list.list_size);
}

/* assignment operator */
template <typename t>
double_list<t> &double_list<t>::operator=(double_list<t> rhs) {
  swap(rhs);
  return *this;
}

template <typename t>
double_list<t> &double_list<t>::operator=(double_list<t> &&rhs) {
  swap(rhs);
  return *this;
}

/* allow */
template <typename t>
std::ostream &operator<<(std::ostream &out, double_list<t> const &l) {
  out << "head";
  for (auto ptr = l.rend(); ptr != nullptr; ptr = ptr->next()) {
    if (ptr == l.end() || ptr == l.rend()) {
      out << "->S";
    } else {
      out << "->" << ptr->value();
    }
  }
  out << "->0" << std::endl
      << "tail";
  for (auto ptr = l.end(); ptr != nullptr; ptr = ptr->previous()) {
    if (ptr == l.end() || ptr == l.rend()) {
      out << "->S";
    } else {
      out << "->" << ptr->value();
    }
  }
  out << "->0";
  return out;
}

} /* namespace AaDS */

#endif
