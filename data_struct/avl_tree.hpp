#pragma once

#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

namespace AaDS {

template <typename t>
class avl_tree {
public:
  class node {
  private:
    t element;
    node *left_node;
    node *right_node;
    int node_height;

  public:
    node(t const & = t(), node * = nullptr, node * = nullptr);
    t value() const;
    node *left() const;
    node *right() const;
    int height() const;
  };

private:
  node *root;
};

template <typename t>
avl_tree<t>::node::node(t const &obj, node *l, node *r)
    : element(obj), left_node(l), right_node(r) {}

template <typename t>
t avl_tree<t>::node::value() const { return element; }

template <typename t>
typename avl_tree<t>::node *avl_tree<t>::node::left() const {
  return left_node;
}

template <typename t>
typename avl_tree<t>::node *avl_tree<t>::node::right() const {
  return right_node;
}

template <typename t>
int avl_tree<t>::node::height() const { return node_height; }

} /* namespace AaDS */

#endif
