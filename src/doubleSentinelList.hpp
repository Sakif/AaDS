#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include "doubleNode.hpp"
#include "exception.hpp"
#include <iostream>

template <typename Type>
class doubleSentinelList {
private:
  doubleNode<Type> *listHead;
  doubleNode<Type> *listTail;
  int listSize;

public:
  doubleSentinelList();
  ~doubleSentinelList();
  doubleSentinelList(doubleSentinelList const &);

  /* Accessors */
  int size() const;
  bool empty() const;

  Type front() const;
  Type back() const;

  doubleNode<Type> *begin() const;
  doubleNode<Type> *end() const;
  doubleNode<Type> *rbegin() const;
  doubleNode<Type> *rend() const;

  int count(Type const &) const;
  doubleNode<Type> *find(Type const &) const;

  /* Mutators */
  void pushFront(Type const &);
  void pushBack(Type const &);

  Type popFront();
  Type popBack();

  int erase(Type const &);

  template <typename T>
  friend std::ostream &operator<<(std::ostream &, doubleSentinelList<T> const &);
};

template <typename Type> /* The constructor creates two instances of a Double_node<Type> (called the sentinels). The head and tail pointers are set to point to one of the sentinels, each. The values stored in these nodes is not important, you can use the default value or whatever values you want. The previous and next pointers of the head sentinel should be nullptr and the address of the tail sentinel, respectively. The previous and next pointers of the tail sentinel should be address of the head sentinel and nullptr, respectively. The node count is set to 0. */
doubleSentinelList<Type>::doubleSentinelList() : listSize(0), listHead(new doubleNode<Type>()), listTail(new doubleNode<Type>(0, listHead, nullptr)) {
  listHead->nextNode = listTail;
}

template <typename Type> /* The destructor must delete each of the nodes in the list including the sentinels. */
doubleSentinelList<Type>::~doubleSentinelList() {
  while (!empty())
    popFront();
  delete listHead;
  delete listTail;
}

template <typename Type> /* The copy constructor must create a new doubly linked list with a copy of all of the nodes within the linked list pass as the argument list with the values stored in the same order. The linked list passed as an argument may not be changed. Once a copy is made, any change to the original linked list must not affect the copy. */
doubleSentinelList<Type>::doubleSentinelList(doubleSentinelList const &other) : listSize(0), listHead(new doubleNode<Type>()), listTail(new doubleNode<Type>(0, listHead, nullptr)) {
  listHead->nextNode = listTail;
  for (auto node = other.begin(); node != other.end(); node = node->next())
    pushBack(node->value());
}

template <typename Type> /* Returns the number of items in the list. */
int doubleSentinelList<Type>::size() const { return listSize; }

template <typename Type> /* Returns true if the list is empty, false otherwise. */
bool doubleSentinelList<Type>::empty() const { return size() == 0; }

template <typename Type> /* Retrieves the object stored in the node pointed to by the next pointer of the head sentinel. This function throws a underflow if the list is empty. */
Type doubleSentinelList<Type>::front() const {
  if (empty())
    throw underflow();
  return begin()->value();
}

template <typename Type> /* Retrieves the object stored in the node pointed to by the previous pointer of the tail sentinel. This function throws a underflow if the list is empty. */
Type doubleSentinelList<Type>::back() const {
  if (empty())
    throw underflow();
  return rbegin()->value();
}

template <typename Type> /* Returns the address stored by the next pointer of the head sentinel node. */
doubleNode<Type> *doubleSentinelList<Type>::begin() const { return listHead->next(); }

template <typename Type> /* Returns the address of the tail sentinel node. */
doubleNode<Type> *doubleSentinelList<Type>::end() const { return listTail; }

template <typename Type> /* Returns the address stored by the previous pointer of the tail sentinel node. */
doubleNode<Type> *doubleSentinelList<Type>::rbegin() const { return listTail->previous(); }

template <typename Type> /* Returns the address of the head sentinel node. */
doubleNode<Type> *doubleSentinelList<Type>::rend() const { return listHead; }

template <typename Type> /* Returns the number of nodes in the linked list storing a value equal to the argument. */
int doubleSentinelList<Type>::count(const Type &obj) const {
  int hits = 0;
  for (auto node = begin(); node != end(); node = node->next()) {
    if (node->value() == obj)
      hits++;
  }
  return hits;
}

template <typename Type> /* Returns the address of the first node in the linked list storing a value equal to the argument; if none is found, return end(). */
doubleNode<Type> *doubleSentinelList<Type>::find(const Type &obj) const {
  auto node = begin();
  while (node != end()) {
    if (node->value() == obj)
      return node;
    node = node->next();
  }
  return node;
}

template <typename Type> /* Creates a new doubleNode<Type> storing the argument new_value, the next pointer of which is set to the next pointer of the sentinel and the previous pointer is set to point to the sentinel. The next pointer of the sentinel and the previous pointer of what was the first node are set to this new node. */
void doubleSentinelList<Type>::pushFront(const Type &obj) {
  auto node = new doubleNode<Type>(obj, listHead, listHead->next());
  listHead->next()->previousNode = node;
  listHead->nextNode = node;
  listSize++;
}

template <typename Type> /* Similar to pushFront, this places a new node at the back of the list storing the argument new value. */
void doubleSentinelList<Type>::pushBack(const Type &obj) {
  auto node = new doubleNode<Type>(obj, listTail->previous(), listTail);
  listTail->previous()->nextNode = node;
  listTail->previousNode = node;
  listSize++;
}

template <typename Type> /* Delete the first non-sentinel node at the front of the linked list and update the previous and next pointers of any other node (including possibly the sentinels) within the list as necessary. Throw an underflow exception if the list is empty. */
Type doubleSentinelList<Type>::popFront() {
  auto value = front();
  auto node = begin();
  listHead->nextNode = node->next();
  node->next()->previousNode = listHead;
  listSize--;
  delete node;
  return value;
}

template <typename Type> /* Similar to pop_front, delete the last non-sentinel node in the list. This function throws a underflow if the list is empty. */
Type doubleSentinelList<Type>::popBack() {
  auto value = back();
  auto node = rbegin();
  listTail->previousNode = node->previous();
  node->previous()->nextNode = listTail;
  listSize--;
  delete node;
  return value;
}

template <typename Type> /* Delete all the nodes in the linked list that have a value equal to the argument value (use == to to test for equality with the retrieved element). Update the previous and next pointers of any other node (including possibly the sentinels) within the list. Return the number of nodes that were deleted. */
int doubleSentinelList<Type>::erase(const Type &obj) {
  int killCount = 0;
  for (auto node = begin(); node != end(); node = node->next()) {
    if (node->value() == obj) {
      auto temp = node;
      node = node->previous();
      node->nextNode = temp->next();
      temp->next()->previousNode = node;
      delete temp;
      killCount++;
      listSize--;
    }
  }
  return killCount;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, doubleSentinelList<T> const &list) {
  out << "H→T:";
  for (auto ptr = list.rend(); ptr != nullptr; ptr = ptr->next()) {
    if (ptr == list.rend() || ptr == list.end())
      out << "→S";
    else
      out << "→" << ptr->value();
  }
  out << "→0\nT→H:";
  for (auto ptr = list.end(); ptr != nullptr; ptr = ptr->previous()) {
    if (ptr == list.rend() || ptr == list.end())
      out << "→S";
    else
      out << "→" << ptr->value();
  }
  out << "→0";
  return out;
}

#endif
