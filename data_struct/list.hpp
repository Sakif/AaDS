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
    friend class double_list<type>;
  };

  /* constructior */
  double_list();
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

template <typename t>
/* node constructor */
double_list<t>::node::node(
    t const &obj,
    double_list<t>::node *pn,
    double_list<t>::node *nn)
    : element(obj),
      next_node(nn),
      previous_node(pn) {}

template <typename t>
/* Returns the next pointer. O(1) */
typename double_list<t>::node *double_list<t>::node::next() const {
  return next_node;
}

template <typename t>
/* Returns the previous pointer. O(1) */
typename double_list<t>::node *double_list<t>::node::previous() const {
  return previous_node;
}

template <typename t>
/* Returns the value of the node. O(1) */
t double_list<t>::node::value() const {
  return element;
}

template <typename t>
/* changes the value of the node */
void double_list<t>::node::set(const t &v) {
  element = v;
}

template <typename t>
double_list<t>::double_list()
    : list_head(new node()),
      list_tail(new node(0, list_head)),
      list_size(0) {
  list_head->next_node = list_tail;
}

template <typename t>
/* distructor */
double_list<t>::~double_list() {
  while (!empty()) {
    pop_front();
  }
  delete list_head;
  delete list_tail;
}

template <typename t>
/* Returns the number of items in the list. O(1) */
unsigned double_list<t>::size() const {
  return list_size;
}

template <typename t>
/* Returns true if the list is empty, false otherwise. O(1) */
bool double_list<t>::empty() const {
  return (size() == 0);
}

template <typename t>
/* Returns the number of nodes in the linked list storing a value equal to the
 * argument. O(n) */
unsigned double_list<t>::count(const t &obj) const {
  auto obj_count = 0U;
  for (auto node = begin(); node != end(); node = node->next()) {
    if (node->value() == obj) {
      obj_count++;
    }
  }
  return obj_count;
}

template <typename t>
/* Retrieves the object stored in the node pointed to by the next pointer of the
 * head sentinel. This function throws a underflow if the list is empty. O(1) */
t double_list<t>::front() const {
  if (empty()) {
    throw std::underflow_error("List is empty.");
  }
  return begin()->value();
}

template <typename t>
/* Retrieves the object stored in the node pointed to by the previous pointer
 * of the tail sentinel. This function throws a underflow if the list is empty.
 * O(1) */
t double_list<t>::back() const {
  if (empty()) {
    throw std::underflow_error("List is empty.");
  }
  return rbegin()->value();
}

template <typename t>
/* Returns the address stored by the next pointer of the head sentinel node.
 * O(1) */
typename double_list<t>::node *double_list<t>::begin() const {
  return list_head->next();
}

template <typename t>
/* Returns the address of the tail sentinel node. O(1) */
typename double_list<t>::node *double_list<t>::end() const {
  return list_tail;
}

template <typename t>
/* Returns the address stored by the previous pointer of the tail sentinel
 * node. O(1) */
typename double_list<t>::node *double_list<t>::rbegin() const {
  return list_tail->previous();
}

template <typename t>
/* Returns the address of the head sentinel node. O(1) */
typename double_list<t>::node *double_list<t>::rend() const {
  return list_head;
}

template <typename t>
/* Returns the address of the first node in the linked list storing a value
 * equal to the argument; if none is found, return end(). O(n) */
typename double_list<t>::node *double_list<t>::find(const t &obj) const {
  for (auto node = begin(); node != end(); node = node->next()) {
    if (node->value() == obj) {
      return node;
    }
  }
  return end();
}

template <typename t>
/* Creates a new Double_node<Type> storing the argument new_value, the next
 * pointer of which is set to the next pointer of the sentinel and the previous
 * pointer is set to point to the sentinel. The next pointer of the sentinel
 * and the previous pointer of what was the first node are set to this new
 * node. O(1) */
void double_list<t>::push_front(t const &obj) {
  auto new_node = new node(obj, rend(), begin());
  begin()->previous_node = new_node;
  rend()->next_node = new_node;
  list_size++;
}

template <typename t>
/* Similar to push_front, this places a new node at the back of the list storing
 * the argument new_value. O(1) */
void double_list<t>::push_back(t const &obj) {
  auto new_node = new node(obj, rbegin(), end());
  rbegin()->next_node = new_node;
  end()->previous_node = new_node;
  list_size++;
}

template <typename t>
/* Delete the first non-sentinel node at the front of the linked list and update
 * the previous and next pointers of any other node (including possibly the
 * sentinels) within the list as necessary. Throw an underflow exception if the
 * list is empty. O(1) */
t double_list<t>::pop_front() {
  auto value = front();
  auto node = begin();
  rend()->next_node = node->next();
  node->next()->previous_node = rend();
  list_size--;
  delete node;
  return value;
}

template <typename t>
/* Similar to pop_front, delete the last non-sentinel node in the list. This
 * function throws a underflow if the list is empty. O(1) */
t double_list<t>::pop_back() {
  auto value = back();
  auto node = rbegin();
  end()->previous_node = node->previous();
  node->previous()->next_node = end();
  list_size--;
  delete node;
  return value;
}

template <typename t>
/* Delete all the nodes in the linked list that have a value equal to the
 * argument value (use == to to test for equality with the retrieved element).
 * Update the previous and next pointers of any other node (including possibly
 * the sentinels) within the list. Return the number of nodes that were
 * deleted. O(n) */
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

} // namespace AaDS

#endif
