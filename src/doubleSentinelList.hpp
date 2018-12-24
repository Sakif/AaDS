#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include "Exception.h"
#include <iostream>

template <typename type>
class doubleSentinelList {
public:
  class doubleNode {
  public:
    type nodeValue;
    doubleNode *nextNode;
    doubleNode *previousNode;

    doubleNode(type const & = type(), doubleNode * = nullptr, doubleNode * = nullptr);

    type value() const;
    doubleNode *next() const;
    doubleNode *previous() const;
  };
  // Constructor
  doubleSentinelList();
  ~doubleSentinelList();

  // Accessors
  unsigned int size() const;
  bool empty() const;

  doubleNode *end() const;
  doubleNode *rend() const;
  doubleNode *begin() const;
  doubleNode *rbegin() const;

  type front() const;
  type back() const;

  // Mutators
  void pushFront(type const &);
  void pushBack(type const &);
  void popFront();
  void popBack();

private:
  unsigned int listSize;
  doubleNode *listHead;
  doubleNode *listTail;
};

template <typename type>
doubleSentinelList<type>::doubleNode::doubleNode(type const &nv, doubleNode *pn, doubleNode *nn) {
  nodeValue = nv;
  previousNode = pn;
  nextNode = nn;
}

template <typename type>
type doubleSentinelList<type>::doubleNode::value() const {
  return nodeValue;
}

template <typename type>
typename doubleSentinelList<type>::doubleNode *doubleSentinelList<type>::doubleNode::next() const {
  return nextNode;
}

template <typename type>
typename doubleSentinelList<type>::doubleNode *doubleSentinelList<type>::doubleNode::previous() const {
  return previousNode;
}

template <typename type>
doubleSentinelList<type>::doubleSentinelList() : listSize(0), listHead(new doubleNode()), listTail(new doubleNode(0, listHead, nullptr)) {
  listHead->nextNode = listTail;
}

template <typename type>
doubleSentinelList<type>::~doubleSentinelList() {
  while (!empty())
    popFront();
  delete listHead;
  delete listTail;
}

template <typename type>
unsigned int doubleSentinelList<type>::size() const {
  return listSize;
}

template <typename type>
bool doubleSentinelList<type>::empty() const {
  return size() == 0;
}

template <typename type>
typename doubleSentinelList<type>::doubleNode *doubleSentinelList<type>::end() const {
  return listTail;
}

template <typename type>
typename doubleSentinelList<type>::doubleNode *doubleSentinelList<type>::rend() const {
  return listHead;
}

template <typename type>
typename doubleSentinelList<type>::doubleNode *doubleSentinelList<type>::begin() const {
  if (empty())
    throw underflow();
  return rend()->next();
}

template <typename type>
typename doubleSentinelList<type>::doubleNode *doubleSentinelList<type>::rbegin() const {
  if (empty())
    throw underflow();
  end()->previous();
}

template <typename type>
type doubleSentinelList<type>::front() const {
  return begin()->value();
}

template <typename type>
type doubleSentinelList<type>::back() const {
  return rbegin()->value();
}

template <typename type>
void doubleSentinelList<type>::pushFront(type const &v) {
  listSize++;
  auto n = new doubleNode(v, rend(), rend()->next());
  n->next()->previousNode = n;
  rend()->nextNode = n;
}

template <typename type>
void doubleSentinelList<type>::pushBack(type const &v) {
  listSize++;
  auto n = new doubleNode(v, end()->previous(), end());
  end()->previousNode = n;
  n->previous()->nextNode = n;
}

template <typename type>
void doubleSentinelList<type>::popFront() {
  if (empty())
    throw underflow();
  auto n = begin();
  n->next()->previousNode = rend();
  rend()->nextNode = n->next();
  delete n;
  listSize--;
}

template <typename type>
void doubleSentinelList<type>::popBack() {
  if (empty())
    throw underflow();
  auto n = rbegin();
  end()->previousNode = n->previous();
  n->previous()->nextNode = end();
  delete n;
  listSize--;
}

#endif