#pragma once
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <algorithm>

namespace AaDS {

class array
{
private:
  unsigned array_capacity;
  int* internal_array;
  unsigned array_size;

public:
  array(int = 10);

  /* Accessors */
  unsigned size() const;
  unsigned capacity() const;
  bool empty() const;
  bool full() const;

  /* statistical functions */
  unsigned sum() const;
  double average() const;
  double variance() const;
  double std_dev() const;

  /* Mutators */
  bool append(int);
  void clear();
};

/* Constructor
 *
 * Create a new array with a capacity of at least one. The default value of the argument is 10.
 *
 * The array is initially empty, and there is no need to zero out the entries of the array;
 */
array::array(int n)
  : array_capacity(std::max(1, n))
  , internal_array(new int[array_capacity])
  , array_size(0)
{}

unsigned
array::size() const
{
  return array_size;
}

bool
array::empty() const
{
  return (size() == 0);
}

void
array::clear()
{
  array_size = 0;
}

bool
array::append(int n)
{
  if (array_size >= array_capacity) {
    return false;
  }
  internal_array[array_size++] = n;
  return true;
}

unsigned
array::sum() const
{
  auto sum = 0U;
  for (auto i = 0U; i < size(); i++) {
    sum += internal_array[i];
  }
  return sum;
}

}
#endif
