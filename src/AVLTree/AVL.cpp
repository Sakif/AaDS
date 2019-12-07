#include "AVL.hpp"

template <typename type>
AVLTree<type>::Tree::Tree(type val) {
  data = val;
  height = 0;
  parent = nullptr;
  left = nullptr;
  right = nullptr;
}

template <typename type>
int AVLTree<type>::Tree::updateHeight() {
  if (left != nullptr && right != nullptr) {
    if (left->getHeight() > right->getHeight())
      height = left->getHeight() + 1;
    else
      height = right->getHeight() + 1;
  } else if (left != nullptr)
    height = left->getHeight() + 1;
  else if (right != nullptr)
    height = right->getHeight() + 1;
  else
    height = 0;
  return height;
}
