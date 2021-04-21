#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <stdexcept>

#ifndef ARRAY_HPP
#define ARRAY_HPP

namespace AaDS {

class array {
private:
  unsigned array_capacity;
  int *internal_array;
  unsigned array_size;

public:
  array(int = 10);
  array(array const &);
  ~array();

  /* Accessors */
  unsigned size() const;
  unsigned capacity() const;
  bool empty() const;
  bool full() const;
  int operator[](unsigned n) const;

  /* statistical functions */
  unsigned sum() const;
  double average() const;
  double variance() const;
  double std_dev() const;

  /* Mutators */
  bool append(int);
  void clear();
  void swap(array &other);
};

/* Constructor
 *
 * Create a new array with a capacity of at least one. The default value of the argument is 10.
 *
 * The array is initially empty, and there is no need to zero out the entries of the array;
 */
array::array(int n)
    : array_capacity(std::max(1, n)),
      internal_array(new int[array_capacity]),
      array_size(0) {}

/* copy constructor */
array::array(array const &o)
    : array_capacity(o.array_capacity),
      internal_array(new int[array_capacity]),
      array_size(o.array_size) {
  /* copy all the entities from the other array */
  for (auto i = 0U; i < size(); i++) {
    internal_array[i] = o.internal_array[i];
  }
}

/* distructor */
array::~array() {
  delete[] internal_array;
}

/* returns the size of the array */
unsigned array::size() const {
  return array_size;
}

/* shows if the array is empty or not */
bool array::empty() const {
  return (size() == 0);
}

/* clears the array by setting the array_size to 0 */
void array::clear() {
  array_size = 0;
}

/* shows the capacity of the array */
unsigned array::capacity() const {
  return array_capacity;
}

/* adds item to the end of the array */
bool array::append(int n) {
  if (size() >= capacity()) {
    /* cannot append if array is full */
    return false;
  }

  internal_array[array_size] = n;
  array_size++;
  return true;
}

/* adds all the items in the array and returns the sum */
unsigned array::sum() const {
  auto sum = 0U;
  for (auto i = 0U; i < size(); i++) {
    sum += internal_array[i];
  }
  return sum;
}

/* calculates the average of the array */
double array::average() const {
  if (size() < 1) {
    throw std::underflow_error("Average requires at least 1 item");
  }
  return static_cast<double>(sum()) / static_cast<double>(size());
}

/* calculates the sample veriance of all the items in the array */
double array::variance() const {
  if (size() < 2) {
    throw std::underflow_error("Variance requires at least 2 items");
  }
  auto exp = average();
  auto var = 0.0;

  for (auto i = 0U; i < size(); i++) {
    var += pow(internal_array[i] - exp, 2.0);
  }

  return var / (size() - 1);
}

/* calculates the standerd deviation of the array */
double array::std_dev() const {
  return sqrt(variance());
}

int array::operator[](unsigned n) const {
  return internal_array[n];
}

/* swap */
void array::swap(array &other) {
  std::swap(array_capacity, other.array_capacity);
  std::swap(internal_array, other.internal_array);
  std::swap(array_size, other.array_size);
}

} // namespace AaDS

#endif
