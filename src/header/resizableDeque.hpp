#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#pragma once
#include "exception.hpp"

template <typename type>
class resizableDeque {
private:
  unsigned initialArrayCapacity;
  unsigned arrayCapacity;
  unsigned dequeSize;
  type *array;
  int iFront;
  int iBack;

public:
  resizableDeque(unsigned = 16);
  ~resizableDeque();

  unsigned size() const;
  bool empty() const;
  unsigned capacity() const;
};

template <typename type>
resizableDeque<type>::resizableDeque(unsigned n) : initialArrayCapacity(n), arrayCapacity(initialArrayCapacity), dequeSize(0), array(new type[arrayCapacity]) {}

template <typename type>
resizableDeque<type>::~resizableDeque() {
  delete array;
}

template <typename type>
unsigned resizableDeque<type>::size() const { return dequeSize; }

template <typename type>
bool resizableDeque<type>::empty() const { return size() == 0; }

template <typename type>
unsigned resizableDeque<type>::capacity() const { return arrayCapacity; }

#endif
