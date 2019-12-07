#ifndef AVL_TREE
#define AVL_TREE

template <typename type>
class AVLTree {
private:
  class Tree {
  private:
    type data;
    int height;
    Tree* parent;
    Tree* left;
    Tree* right;

  public:
    // constructor
    Tree(type);

    // access
    type getDate() const { return data; }
    int getHeight() const { return height; }

    // mutator
    int updateHeight();
  };
};

#endif
