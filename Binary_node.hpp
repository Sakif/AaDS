#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>

template <typename Type>
class AVL_tree {
private:
	class Node {
	private:
		Type node_value;
		Node *left_tree;
		Node *right_tree;
		int tree_height;

	public:
		Node(Type const & = Type());

		Type value() const;
		Node *left() const;
		Node *right() const;
		bool is_leaf() const;
		int height() const;
		Node *find(Type const &obj) const;

		void clear();
		void update_height();
		bool insert(Type const &obj, Node *&to_this);
		friend class AVL_tree;
	};
	Node *root_node;
	int tree_size;

public:
	AVL_tree();
	int size() const;
	bool empty() const;
};

template <typename Type>
void AVL_tree<Type>::Node::update_height() {
	tree_height = std::max(left()->height(), right()->height()) + 1;
}

template <typename Type>
AVL_tree<Type>::Node::Node(Type const &obj) {
	node_value = obj;
	tree_height = 0;
	left_tree = nullptr;
	right_tree = nullptr;
}

template <typename Type>
Type AVL_tree<Type>::Node::value() const {
	return node_value;
}

template <typename Type>
typename AVL_tree<Type>::Node *AVL_tree<Type>::Node::left() const {
	return left_tree;
}

template <typename Type>
typename AVL_tree<Type>::Node *AVL_tree<Type>::Node::right() const {
	return right_tree;
}

template <typename Type>
bool AVL_tree<Type>::Node::is_leaf() const {
	return (left() == nullptr && right() == nullptr);
}

template <typename Type>
int AVL_tree<Type>::Node::height() const {
	return (this == nullptr) ? -1 : tree_height;
}

template <typename Type>
typename AVL_tree<Type>::Node *AVL_tree<Type>::Node::find(const Type &obj) const {
	if (value() == obj)
		return this;
	else if (obj < value())
		return (left() == nullptr) ? nullptr : left()->find(obj);
	else
		return (right() == nullptr) ? nullptr : right()->find(obj);
}

template <typename Type>
void AVL_tree<Type>::Node::clear() {
	if (left() != nullptr)
		left_tree->clear();
	if (right() != nullptr)
		right_tree->clear();
	delete this;
}

template <typename Type>
bool AVL_tree<Type>::Node::insert(const Type &obj, Node *&to_this) {
	if (obj < node_value) {
		if (left() == nullptr) {
			left_tree = new Node(obj);
			update_height();
			return true;
		} else {
			if (left()->insert(obj, left())) {
				update_height();
				return true;
			} else
				return false;
		}
	} else if (obj > node_value) {
		if (right() == nullptr) {
			right_tree = new Node(obj);
			update_height();
			return true;
		} else {
			if (right()->insert(obj, right())) {
				update_height();
				return true;
			} else
				return false;
		}
	} else
		return false;
}

template <typename Type>
bool AVL_tree<Type>::empty() const {
	return size() == 0;
}

template <typename Type>
int AVL_tree<Type>::size() const {
	return tree_size;
}

template <typename Type>
AVL_tree<Type>::AVL_tree() {
	root_node = nullptr;
	tree_size = 0;
}

#endif
