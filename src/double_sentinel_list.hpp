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

  /* Retrieves the object stored in the node pointed to by the next pointer of the head sentinel. This function throws a underflow if the list is empty. (O(1)) */
  t front() const;
  /* Retrieves the object stored in the node pointed to by the previous pointer of the tail sentinel. This function throws a underflow if the list is empty. (O(1)) */
  t back() const;

  /* Returns the address stored by the next pointer of the head sentinel node. (O(1)) */
  node *begin() const;
  /* Returns the address of the tail sentinel node. (O(1)) */
  node *end() const;
  /* Returns the address stored by the previous pointer of the tail sentinel node. (O(1)) */
  node *rbegin() const;
  /* Returns the address of the head sentinel node. (O(1)) */
  node *rend() const;

  /**/
  node *find(t const &) const;
  /* Returns the number of nodes in the linked list storing a value equal to the argument. (O(n)) */
  unsigned count(t const &) const;

  /* mutators */
  void swap(double_sentinel_list &);
  double_sentinel_list &operator=(double_sentinel_list);
  double_sentinel_list &operator=(double_sentinel_list &&);

  /* Creates a new Double_node<Type> storing the argument new_value, the next pointer of which is set to the next pointer of the sentinel and the previous pointer is set to point to the sentinel. The next pointer of the sentinel and the previous pointer of what was the first node are set to this new node. (O(1)) */
  void push_front(t const &);
  /* Similar to push_front, this places a new node at the back of the list storing the argument new_value. (O(1)) */
  void push_back(t const &);

  /* Delete the first non-sentinel node at the front of the linked list and update the previous and next pointers of any other node (including possibly the sentinels) within the list as necessary. Throw an underflow exception if the list is empty. (O(1)) */
  void pop_front();
  /* Similar to pop_front, delete the last non-sentinel node in the list. This function throws a underflow if the list is empty. (O(1)) */
  void pop_back();

  int erase(t const &);

  /* friends */
  template <typename T>
  friend std::ostream &operator<<(std::ostream &, double_sentinel_list<T> const &);

private:
  node *list_head;
  node *list_tail;
  unsigned list_size;
};

/* node */
/* constructors */
template <typename t>
double_sentinel_list<t>::node::node(
    t const &nv, node *pn, node *nn)
    : node_value(nv), previous_node(pn), next_node(nn) {}

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
  return size() == 0 &&
         begin() == end() &&
         rbegin() == rend();
}

template <typename t>
t
double_sentinel_list<t>::front() const
{
  if (empty())
  {
    throw std::underflow_error("List is empty!");
  }

  return begin()->value();
}

template <typename t>
t
double_sentinel_list<t>::back() const
{
  if (empty())
  {
    throw std::underflow_error("List is empty!");
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
unsigned
double_sentinel_list<t>::count(const t &v) const
{
  auto count = 0U;
  for (auto n = begin(); n != end(); n = n->next())
  {
    if (n->value() == v)
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
    throw std::underflow_error("List is empty!");
  }

  auto nTdel = begin();
  nTdel->previous()->next_node = nTdel->next();
  nTdel->next()->previous_node = nTdel->previous();
  delete nTdel;
  list_size--;
}

template <typename t>
void
double_sentinel_list<t>::pop_back()
{
  if (empty())
  {
    throw std::underflow_error("List is empty!");
  }

  auto nTdel = rbegin();
  nTdel->previous()->next_node = nTdel->next();
  nTdel->next()->previous_node = nTdel->previous();
  delete nTdel;
  list_size--;
}

#endif
