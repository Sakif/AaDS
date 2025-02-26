#ifndef DYNAMIC_DEQUE_HPP
#define DYNAMIC_DEQUE_HPP

#include <iostream>
#include <ostream>
#include <stdexcept>

template <typename t>
class dynamic_deque
{
private:
  unsigned initial_array_capacity;
  unsigned array_capacity;
  unsigned deque_size;
  unsigned ifront;
  unsigned iback;
  t *array;

public:
  /** The constructor takes as an argument the initial capacity of the array and
   * allocates memory for that array. The initial array capacity must be 16 or
   * more, with a default capacity of 16. If the user passes a value less than
   * 16, use 16. Other member variables are assigned as appropriate. */
  dynamic_deque(unsigned = 16);
  dynamic_deque(dynamic_deque const &);
  dynamic_deque(dynamic_deque &&);
  /** The destructor deletes the memory allocated for the array. */
  ~dynamic_deque();

  t front() const;
  t back() const;
  /** Returns the number of elements currently stored in the deque. (O(1)) */
  unsigned size() const;
  /** Returns true if the deque is empty, false otherwise. (O(1)) */
  bool empty() const;
  /** Returns the current capacity of the array. (O(1)) */
  unsigned capacity() const;

  void swap(dynamic_deque &);
  dynamic_deque &operator=(dynamic_deque const &);
  dynamic_deque &operator=(dynamic_deque &&);
  void push_front(t const &);
  void push_back(t const &);
  void pop_front();
  void pop_back();
  void clear();

  template <typename T>
  friend std::ostream &operator<<(std::ostream &, dynamic_deque<T> const &);
};

template <typename t>
dynamic_deque<t>::dynamic_deque(
    unsigned isize)
    : initial_array_capacity(isize),
      array_capacity(initial_array_capacity),
      deque_size(0),
      ifront(0),
      iback(0)
{
  array = new t[array_capacity];
}

template <typename t>
dynamic_deque<t>::~dynamic_deque()
{
  delete array;
}

template <typename t>
unsigned
dynamic_deque<t>::capacity() const
{
  return array_capacity;
}

template <typename t>
unsigned
dynamic_deque<t>::size() const
{
  return deque_size;
}

template <typename t>
bool
dynamic_deque<t>::empty() const
{
  return size() == 0;
}

template <typename t>
t
dynamic_deque<t>::front() const
{
  if (empty())
  {
    throw std::underflow_error("Cannot get first element, queue is empty.");
  }
  return array[ifront];
}

#endif
