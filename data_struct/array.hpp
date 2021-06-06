#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <ostream>
#include <stdexcept>

#ifndef ARRAY_HPP
#define ARRAY_HPP

namespace AaDS {

template <typename type>
class array {
private:
  unsigned array_capacity;
  type *internal_array;
  unsigned array_size;

public:
  array(int = 10);
  array(array const &);
  ~array();

  /* accessors */
  unsigned size() const;
  unsigned capacity() const;
  bool empty() const;
  bool full() const;
  type operator[](unsigned n) const;

  /* statistical functions */
  type sum() const;
  double average() const;
  double variance() const;
  double std_dev() const;

  /* mutators */
  bool append(type);
  void clear();
  void swap(array &other);
  array &operator=(array);

  /* A friend to print the array */
  template <typename t>
  friend std::ostream &operator<<(std::ostream &, array<t> const &);
};

/* Constructor */
template <typename type>
array<type>::array(int n)
    : array_capacity(std::max(1, n)),
      internal_array(new int[array_capacity]),
      array_size(0) {}

/* copy constructor */
template <typename type>
array<type>::array(array const &o)
    : array_capacity(o.array_capacity),
      internal_array(new int[array_capacity]),
      array_size(o.array_size) {
  /* copy all the entities from the other array */
  for (auto i = 0U; i < size(); i++) {
    internal_array[i] = o.internal_array[i];
  }
}

/* distructor */
template <typename type>
array<type>::~array() { delete[] internal_array; }

/* returns the size of the array */
template <typename type>
unsigned array<type>::size() const { return array_size; }

/* shows if the array is empty or not */
template <typename type>
bool array<type>::empty() const { return (size() == 0); }

/* clears the array by setting the array_size to 0 */
template <typename type>
void array<type>::clear() { array_size = 0; }

/* shows the capacity of the array */
template <typename type>
unsigned array<type>::capacity() const { return array_capacity; }

/* adds item to the end of the array */
template <typename type>
bool array<type>::append(type n) {
  /* cannot append if array is full */
  if (size() >= capacity()) {
    return false;
  }

  internal_array[array_size] = n;
  array_size++;
  return true;
}

/* adds all the items in the array and returns the sum */
template <typename type>
type array<type>::sum() const {
  type sum = 0;
  for (auto i = 0U; i < size(); i++) {
    sum += internal_array[i];
  }
  return sum;
}

/* calculates the average of the array */
template <typename type>
double array<type>::average() const {
  if (size() < 1) {
    throw std::underflow_error("Average requires at least 1 item");
  }
  return static_cast<double>(sum()) / static_cast<double>(size());
}

/* swap */
template <typename type>
void array<type>::swap(array &other) {
  std::swap(array_capacity, other.array_capacity);
  std::swap(internal_array, other.internal_array);
  std::swap(array_size, other.array_size);
}

/* calculates the sample veriance of all the items in the array */
template <typename type>
double array<type>::variance() const {
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
template <typename type>
double array<type>::std_dev() const { return sqrt(variance()); }

/* accessing the internal array with the index operator */
template <typename type>
type array<type>::operator[](unsigned n) const { return internal_array[n]; }

/* assignment operator */
template <typename type>
array<type> &array<type>::operator=(array rhs) {
  swap(rhs);
  return *this;
}

/* outputs to ostream */
template <typename type>
std::ostream &operator<<(std::ostream &out, array<type> const &para) {
  if (para.empty()) {
    out << "-";
  } else {
    out << para.internal_array[0];
  }

  for (auto i = 1U; i < para.size(); i++) {
    out << " " << para.internal_array[i];
  }

  for (auto i = para.size(); i < para.capacity(); i++) {
    out << " -";
  }

  return out;
}

double factorial(unsigned n) {
  auto r = 1.0;
  for (double d = 2.0; d < n; d += 1.0) {
    r *= d;
  }
  return r;
}

double factorial_r(unsigned n) {
  if (n < 2) {
    return 1;
  } else {
    return n * factorial_r(n - 1);
  }
}

double fibonacci(int n) {
  double phi = std::sqrt(5.0) + 1.0;
  phi /= 2.0;
  auto result = std::pow(phi, n) - std::pow(1 - phi, n);
  result /= std::sqrt(5.0);
  return std::floor(result + 0.5);
}

unsigned long long fibonacci_r(int n) {
  if (n < 3) {
    return 1;
  } else {
    return fibonacci_r(n - 1) + fibonacci_r(n - 2);
  }
}

} /* namespace AaDS */

#endif
