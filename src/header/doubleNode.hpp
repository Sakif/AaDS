#ifndef DOUBLE_NODE_H
#define DOUBLE_NODE_H

#include <iostream>

template <typename Type>
class doubleSentinelList;

template <typename Type>
class doubleNode {
private:
  Type element;
  doubleNode *nextNode;
  doubleNode *previousNode;

public:
  doubleNode(Type const & = Type(), doubleNode * = nullptr, doubleNode * = nullptr);

  Type value() const;
  doubleNode *previous() const;
  doubleNode *next() const;

  friend class doubleSentinelList<Type>;
};

template <typename Type>
doubleNode<Type>::doubleNode(Type const &e, doubleNode<Type> *p, doubleNode<Type> *n) : element(e), previousNode(p), nextNode(n) {}

template <typename Type>
Type doubleNode<Type>::value() const { return element; }

template <typename Type>
doubleNode<Type> *doubleNode<Type>::previous() const { return previousNode; }

template <typename Type>
doubleNode<Type> *doubleNode<Type>::next() const { return nextNode; }

#endif
