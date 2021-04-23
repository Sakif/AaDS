#pragma once
#include <iosfwd>
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

  /* accessors */
  unsigned size() const;
  bool empty() const;
  type front() const;
  type back() const;

  node *begin() const;
  node *end() const;
  node *rbegin() const;
  node *rend() const;

private:
  node *list_head;
  node *list_tail;
  unsigned list_size;

  template <typename t>
  friend std::ostream &operator<<(std::ostream &, double_list<t> const &);
};

template <typename t>
double_list<t>::node::node(
    t const &obj,
    double_list<t>::node *pn,
    double_list<t>::node *nn)
    : element(obj),
      next_node(nn),
      previous_node(pn) {}

template <typename t>
typename double_list<t>::node *double_list<t>::node::next() const {
  return next_node;
}

template <typename t>
typename double_list<t>::node *double_list<t>::node::previous() const {
  return previous_node;
}

template <typename type>
type double_list<type>::node::value() const {
  return element;
}

template <typename t>
double_list<t>::double_list()
    : list_head(new node()),
      list_tail(new node(0, list_head)),
      list_size(0) {
  list_head->next_node = list_tail;
}

template <typename t>
unsigned double_list<t>::size() const {
  return list_size;
}

template <typename t>
bool double_list<t>::empty() const {
  return (size() == 0);
}

template <typename t>
typename double_list<t>::node *double_list<t>::begin() const {
  return list_head->next();
}

template <typename t>
typename double_list<t>::node *double_list<t>::end() const {
  return list_tail;
}

template <typename t>
t double_list<t>::front() const {
  if (empty()) {
    throw std::underflow_error("List is empty.");
  }

  return begin()->value();
}

template <typename t>
t double_list<t>::back() const {
  if (empty()) {
    throw std::underflow_error("List is empty." );
  }
}

} // namespace AaDS

#endif
