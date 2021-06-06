/*
Author: Sakif Fahmid Zaman

A deque stores elements in an ordered list and allows insertions and deletions
at both ends of the list in O(1) time.

The elements in this deque are stored in an array. The capacity of the array may
be changed depending on the number of elements currently stored in the array,
according to the following two rules:

+ If an element is being inserted into a deque where the array is already full,
  the capacity of the array is doubled.
+ If, after removing an element from a deque where the number of elements is 1/4
  the capacity of the array or less, then the capacity of the array is halved.
  The capacity of the array may not be reduced below the initially specified
  capacity.
*/
#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept>

#ifndef DEQUE_HPP
#define DEQUE_HPP

#define DOUBLE(a) a * 2
#define HALF(a) a / 2
#define QUARTER(a) a / 4

namespace AaDS {

template <typename t>
class deque {
private:
  unsigned initial_array_capacity;
  unsigned array_capacity;
  unsigned deque_size;
  int ifront;
  int iback;
  t *internal_array;

  /* for changing the internal array */
  void double_array();
  void half_array();

public:
  deque(int = 16);
  ~deque();

  /* Accessors */
  unsigned size() const;
  bool empty() const;
  t front() const;
  t back() const;
  unsigned capacity() const;

  /* Mutators */
  void push_front(t const &);
  void push_back(t const &);
  t pop_front();
  t pop_back();
  void clear();

  /* Friends */
  template <typename T>
  friend std::ostream &operator<<(std::ostream &, deque<T> const &);
};

/*
The constructor takes as an argument the initial capacity of the array and
allocates memory for that array. The initial array capacity must be 16 or more,
with a default capacity of 16. If the user passes a value less than 16, use 16.
Other member variables are assigned as appropriate.
*/
template <typename t>
deque<t>::deque(int n)
    : initial_array_capacity(std::max(1, n)),
      array_capacity(initial_array_capacity),
      deque_size(0),
      ifront(0),
      iback(0),
      internal_array(new t[array_capacity]) {}

/* The destructor deletes the memory allocated for the array. */
template <typename t>
deque<t>::~deque() {
  delete[] internal_array;
}

/* Returns the number of elements currently stored in the deque. O(1) */
template <typename t>
unsigned deque<t>::size() const {
  return deque_size;
}

/* Returns true if the deque is empty, false otherwise. O(1) */
template <typename t>
bool deque<t>::empty() const {
  return (size() == 0);
}

/*
Return the object at the front of the deque. It may throw a underflow exception.
O(1)
*/
template <typename t>
t deque<t>::front() const {
  if (empty()) {
    throw std::underflow_error("List is empty.");
  }
  return internal_array[ifront];
}

/*
Return the object at the back of the deque. It may throw a underflow exception.
O(1) */
template <typename t>
t deque<t>::back() const {
  if (empty()) {
    throw std::underflow_error("List is empty.");
  }
  return internal_array[iback];
}

/* Returns the current capacity of the array. O(1) */
template <typename t>
unsigned deque<t>::capacity() const {
  return array_capacity;
}

/* doubles the internal array */
template <typename t>
void deque<t>::double_array() {
  auto new_array = new t[DOUBLE(capacity())];
  for (auto new_array_i = 0U; new_array_i < capacity(); new_array_i++) {
    new_array[new_array_i] = internal_array[ifront];
    ++ifront %= capacity();
    iback = ifront;
  }
  ifront = 0;
  array_capacity = DOUBLE(capacity());
  internal_array = new_array;
}

/* halves the internal array */
template <typename t>
void deque<t>::half_array() {
  auto new_array = new t[HALF(capacity())];
  for (auto new_array_i = 0U; new_array_i < HALF(capacity()); new_array_i++) {
    new_array[new_array_i] = internal_array[ifront];
    ++ifront %= capacity();
    iback = ifront;
  }
  ifront = 0;
  array_capacity = HALF(capacity());
  internal_array = new_array;
}

/*
Insert the new element at the front of the deque. If before the element is
placed into the deque, the array is filled, the capacity of the array is
doubled. (O(1) on average)
*/
template <typename t>
void deque<t>::push_front(t const &obj) {
  deque_size++;
  if (size() > capacity()) {
    double_array();
  }
  if (--ifront < 0) {
    ifront += capacity();
  }
  internal_array[ifront] = obj;
}

/*
Insert the new element at the back of the deque. If before the element is placed
into the deque, the array is filled, the capacity of the array is doubled. (O(1)
on average)
*/
template <typename t>
void deque<t>::push_back(t const &obj) {
  deque_size++;
  if (size() > capacity()) {
    double_array();
  }
  ++iback %= capacity();
  internal_array[iback] = obj;
}

/*
Removes the element at the front of the deque. If, after the element is removed,
the array is 1/4 full or less and the array capacity is greater than the initial
capacity, the capacity of the array is halved. This may throw a underflow
exception. (O(1) on average)
*/
template <typename t>
t deque<t>::pop_front() {
  auto return_value = front();
  ++ifront %= capacity();
  deque_size--;
  if (size() <= QUARTER(capacity()) &&
      HALF(capacity()) >= initial_array_capacity) {
    half_array();
  }
  return return_value;
}

/*
Removes the element at the back of the deque. If, after the element is removed,
the array is 1/4 full or less and the array capacity is greater than the initial
capacity, the capacity of the array is halved. This may throw a underflow
exception. (O(1) on average)
*/
template <typename t>
t deque<t>::pop_back() {
  auto return_value = back();
  if (--iback < 0) {
    iback += capacity();
  }
  deque_size--;
  if (size() <= QUARTER(capacity()) &&
      HALF(capacity()) >= initial_array_capacity) {
    half_array();
  }
  return return_value;
}

/*
Empties the deque by resetting the member variables. The array is resized to the
initial capacity. (O(1))
*/
template <typename t>
void deque<t>::clear() {
  array_capacity = initial_array_capacity;
  auto new_array = new t[array_capacity];
  ifront = 0;
  iback = 0;
  deque_size = 0;

  internal_array = new_array;
}

} /* namespace AaDS */

#endif
