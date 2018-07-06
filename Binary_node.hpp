#include <algorithm>

template <typename Type>
class Binary_node {
protected:
	Type node_value;
	Binary_node *left_tree;
	Binary_node *right_tree;

public:
	Binary_node(Type const &);
	Type value() const;
	Binary_node *left() const;
	Binary_node *right() const;
	bool is_leaf() const;
	int size() const;
	int height() const;
	void clear(Binary_node *&);
};

template <typename Type>
Binary_node<Type>::Binary_node(Type const &obj) {
	node_value = obj;
	left_tree = nullptr;
	right_tree = nullptr;
}

template <typename Type>
Type Binary_node<Type>::value() const {
	return node_value;
}

template <typename Type>
Binary_node<Type> *Binary_node<Type>::left() const {
	return left_tree;
}

template <typename Type>
Binary_node<Type> *Binary_node<Type>::right() const {
	return right_tree;
}

template <typename Type>
bool Binary_node<Type>::is_leaf() const {
	return ((left() == nullptr) && (right() == nullptr));
}

template <typename Type>
int Binary_node<Type>::size() const {
	/* where there is no left node: check if there is a right node, if none return 1; else call size on the right node and +1 for the current node */
	if (left() == nullptr)
		return (right() == nullptr) ? 1 : 1 + right()->size();
	/* same as above condition but with a size call on left node even if there is no right node */
	else
		return (right() == nullptr) ? 1 + left()->size() : 1 + left()->size() + right()->size();
}

template <typename Type>
int Binary_node<Type>::height() const {
	/* where there is no left node: check if there is a right node, if none return 0; else call size on the right node and +1 for the current node */
	if (left() == nullptr)
		return (right() == nullptr) ? 0 : 1 + right()->height();
	/* same as above condition but with a size call on left node even if there is no right node */
	else
		return (right() == nullptr) ? 1 + left()->height() : 1 + left()->height() + right()->height();
}

template <typename Type>
void Binary_node<Type>::clear(Binary_node<Type> *&p_to_this) {
	if (left() != nullptr)
		left()->clear(left_tree);
	if (right() != nullptr)
		right()->clear(right_tree);
	delete this;
	p_to_this = nullptr;
}
