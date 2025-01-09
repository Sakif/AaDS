#ifndef DOUBLE_SENTINEL_LIST_HPP
#define DOUBLE_SENTINEL_LIST_HPP

#include <iostream>
#include <stdexcept>

template <typename t>
class double_sentinel_list
{
public:
  class node
  {
  private:
    t node_value;
    node *previous_node;
    node *next_node;

  public:
    node(t const & = t(), node * = nullptr, node * = nullptr);

    /* Returns the value of the node. (O(1)) */
    t value() const;
    /* Returns the previous pointer. (O(1)) */
    node *previous() const;
    /* Returns the next pointer. (O(1)) */
    node *next() const;
    friend double_sentinel_list;
  };

  double_sentinel_list();
  double_sentinel_list(double_sentinel_list const &);
  double_sentinel_list(double_sentinel_list &&);
  ~double_sentinel_list();

  /* accessors */

  /* Returns the number of items in the list. (O(1)) */
  unsigned size() const;
  /* Returns true if the list is empty, false otherwise. (O(1)) */
  bool empty() const;

  /* Retrieves the object stored in the node pointed to by the next pointer of
   * the head sentinel. This function throws a underflow if the list is empty.
   * (O(1)) */
  t front() const;
  /* Retrieves the object stored in the node pointed to by the previous pointer
   * of the tail sentinel. This function throws a underflow if the list is
   * empty. (O(1)) */
  t back() const;

  /* Returns the address stored by the next pointer of the head sentinel node.
   * (O(1)) */
  node *begin() const;
  /* Returns the address of the tail sentinel node. (O(1)) */
  node *end() const;
  /* Returns the address stored by the previous pointer of the tail sentinel
   * node. (O(1)) */
  node *rbegin() const;
  /* Returns the address of the head sentinel node. (O(1)) */
  node *rend() const;

  /* Returns the address of the first node in the linked list storing a value
   * equal to the argument; if none is found, return end(). (O(n)) */
  node *find(t const &) const;
  /* Returns the number of nodes in the linked list storing a value equal to the
   * argument. (O(n)) */
  unsigned count(t const &) const;

  /* mutators */

  void swap(double_sentinel_list &);
  double_sentinel_list &operator=(double_sentinel_list);
  double_sentinel_list &operator=(double_sentinel_list &&);

  /* Creates a new Double_node<Type> storing the argument new_value, the next
   * pointer of which is set to the next pointer of the sentinel and the
   * previous pointer is set to point to the sentinel. The next pointer of the
   * sentinel and the previous pointer of what was the first node are set to
   * this new node. (O(1)) */
  void push_front(t const &);
  /* Similar to push_front, this places a new node at the back of the list
   * storing the argument new_value. (O(1)) */
  void push_back(t const &);

  /* Delete the first non-sentinel node at the front of the linked list and
   * update the previous and next pointers of any other node (including possibly
   * the sentinels) within the list as necessary. Throw an underflow exception
   * if the list is empty. (O(1)) */
  void pop_front();
  /* Similar to pop_front, delete the last non-sentinel node in the list. This
   * function throws a underflow if the list is empty. (O(1)) */
  void pop_back();

  /* Delete all the nodes in the linked list that have a value equal to the
   * argument value. Update the previous and next pointers of any other node
   * (including possibly the sentinels) within the list. Return the number of
   * nodes that were deleted. (O(n)) */
  unsigned erase(t const &);

  /* friends */
  template <typename T>
  friend std::ostream &operator<<(
      std::ostream &,
      double_sentinel_list<T> const &);

private:
  node *list_head;
  node *list_tail;
  unsigned list_size;
};

/* node */
/* constructors */
template <typename t>
double_sentinel_list<t>::node::node(t const &nv, node *pn, node *nn)
    : node_value(nv), previous_node(pn), next_node(nn)
{
}

/* accessors */
template <typename t>
typename double_sentinel_list<t>::node *
double_sentinel_list<t>::node::previous() const
{
  return previous_node;
}

template <typename t>
typename double_sentinel_list<t>::node *
double_sentinel_list<t>::node::next() const
{
  return next_node;
}

template <typename t>
t
double_sentinel_list<t>::node::value() const
{
  return node_value;
}

/* list */
/* constructors */
template <typename t>
double_sentinel_list<t>::double_sentinel_list()
    : list_head(new node()), list_tail(new node(t(), list_head)), list_size(0U)
{
  list_head->next_node = list_tail;
}

template <typename t>
double_sentinel_list<t>::~double_sentinel_list()
{
  while (!empty())
  {
    pop_front();
  }

  delete list_head;
  delete list_tail;
}

/* accessors */
template <typename t>
unsigned
double_sentinel_list<t>::size() const
{
  return list_size;
}

template <typename t>
bool
double_sentinel_list<t>::empty() const
{
  return size() == 0 && begin() == end() && rbegin() == rend();
}

template <typename t>
t
double_sentinel_list<t>::front() const
{
  if (empty())
  {
    throw std::underflow_error("Cannot fetch item at front, list is empty.");
  }

  return begin()->value();
}

template <typename t>
t
double_sentinel_list<t>::back() const
{
  if (empty())
  {
    throw std::underflow_error("Cannot fetch item at back, list is empty.");
  }

  return rbegin()->value();
}

template <typename t>
typename double_sentinel_list<t>::node *
double_sentinel_list<t>::begin() const
{
  return rend()->next();
}

template <typename t>
typename double_sentinel_list<t>::node *
double_sentinel_list<t>::end() const
{
  return list_tail;
}

template <typename t>
typename double_sentinel_list<t>::node *
double_sentinel_list<t>::rbegin() const
{
  return end()->previous();
}

template <typename t>
typename double_sentinel_list<t>::node *
double_sentinel_list<t>::rend() const
{
  return list_head;
}

template <typename t>
typename double_sentinel_list<t>::node *
double_sentinel_list<t>::find(const t &v) const
{
  for (auto itr = begin(); itr != end(); itr = itr->next())
  {
    if (itr->value() == v)
    {
      return itr;
    }
  }
  return end();
}

template <typename t>
unsigned
double_sentinel_list<t>::count(const t &v) const
{
  auto count = 0U;
  for (auto node = begin(); node != end(); node = node->next())
  {
    if (node->value() == v)
    {
      count++;
    }
  }
  return count;
}

/* mutators */
template <typename t>
void
double_sentinel_list<t>::push_front(t const &v)
{
  auto node = new double_sentinel_list<t>::node(v, rend(), begin());
  begin()->previous_node = node;
  rend()->next_node = node;
  list_size++;
}

template <typename t>
void
double_sentinel_list<t>::push_back(t const &v)
{
  auto node = new double_sentinel_list<t>::node(v, rbegin(), end());
  rbegin()->next_node = node;
  end()->previous_node = node;
  list_size++;
}

template <typename t>
void
double_sentinel_list<t>::pop_front()
{
  if (empty())
  {
    throw std::underflow_error("Cannot pop front, list is empty.");
  }

  auto to_del = begin();
  to_del->previous()->next_node = to_del->next();
  to_del->next()->previous_node = to_del->previous();
  delete to_del;
  list_size--;
}

template <typename t>
void
double_sentinel_list<t>::pop_back()
{
  if (empty())
  {
    throw std::underflow_error("Cannot pop back, list is empty.");
  }

  auto to_del = rbegin();
  to_del->previous()->next_node = to_del->next();
  to_del->next()->previous_node = to_del->previous();
  delete to_del;
  list_size--;
}

template <typename t>
unsigned
double_sentinel_list<t>::erase(t const &v)
{
  auto count = 0U;
  for (auto itr = begin(); itr != end(); itr = itr->next())
  {
    if (itr->value() == v)
    {
      auto to_del = itr;
      itr = to_del->previous();
      to_del->previous()->next_node = to_del->next();
      to_del->next()->previous_node = to_del->previous();
      delete to_del;
      list_size--;
      count++;
    }
  }
  return count;
}

template <typename t>
void
double_sentinel_list<t>::swap(double_sentinel_list<t> &list)
{
  std::swap(list_head, list.list_head);
  std::swap(list_tail, list.list_tail);
  std::swap(list_size, list.list_size);
}

template <typename t>
double_sentinel_list<t> &
double_sentinel_list<t>::operator=(double_sentinel_list<t> rhs)
{
  swap(rhs);
  return *this;
}

template <typename t>
double_sentinel_list<t> &
double_sentinel_list<t>::operator=(double_sentinel_list<t> &&rhs)
{
  swap(rhs);
  return *this;
}

template <typename T>
std::ostream &
operator<<(std::ostream &out, double_sentinel_list<T> const &l)
{
  out << "head";

  for (auto ptr = l.rend(); ptr != nullptr; ptr = ptr->next())
  {
    if (ptr == l.rend() || ptr == l.end())
    {
      out << "->S";
    }
    else
    {
      out << "->" << ptr->value();
    }
  }

  out << "->0" << std::endl
      << "tail";

  for (auto ptr = l.end(); ptr != nullptr; ptr = ptr->previous())
  {
    if (ptr == l.rend() || ptr == l.end())
    {
      out << "->S";
    }
    else
    {
      out << "->" << ptr->value();
    }
  }

  out << "->0";

  return out;
}

#endif
