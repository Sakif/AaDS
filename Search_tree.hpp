#ifndef RPOVDGBQN9TIEO3P
#define RPOVDGBQN9TIEO3P

#include "Exception.h"
#include "ece250.h"
#include <cassert>

template <typename Type>
class Search_tree {
public:
	class Iterator;
private:
	class Node {
	public:
		Type node_value;
		int tree_height;
	  
		Node *left_tree;
		Node *right_tree;

		Node *previous_node;
		Node *next_node;

		Node(Type const & = Type());

		void update_height();

		int height() const;
		bool is_leaf() const;
		Node *front();
		Node *back();
		Node *find(Type const &obj);

		void clear();
		bool insert(Type const &obj, Node *&to_this);
		bool erase(Type const &obj, Node *&to_this);
	};

	Node *root_node;
	int tree_size;

	Node *front_sentinel;
	Node *back_sentinel;
public:
	class Iterator {
	private:
		Search_tree *containing_tree;
		Node *current_node;
		bool is_end;

		Iterator(Search_tree *tree, Node *starting_node);
	public:
		Type operator*() const;
		Iterator &operator++();
		Iterator &operator--();
		bool operator==(Iterator const &rhs) const;
		bool operator!=(Iterator const &rhs) const;

		friend class Search_tree;
	};

	Search_tree();
	~Search_tree();

	bool empty() const;
	int size() const;
	int height() const;

	Type front() const;
	Type back() const;

	Iterator begin();
	Iterator end();
	Iterator rbegin();
	Iterator rend();
	Iterator find(Type const &);

	void clear();
	bool insert(Type const &);
	bool erase(Type const &);

	template <typename T>
	friend std::ostream &operator<<(std::ostream &, Search_tree<T> const &);
};

template <typename Type>
Search_tree<Type>::Search_tree() : root_node(nullptr),
				   tree_size(0),
				   front_sentinel(new Search_tree::Node(Type())),
				   back_sentinel(new Search_tree::Node(Type())) {
	front_sentinel->next_node = back_sentinel;
	back_sentinel->previous_node = front_sentinel;
}

template <typename Type>
Search_tree<Type>::~Search_tree() {
	clear();
	delete front_sentinel;
	delete back_sentinel;
}

template <typename Type>
bool Search_tree<Type>::empty() const {
	return (root_node == nullptr);
}

template <typename Type>
int Search_tree<Type>::size() const {
	return tree_size;
}

template <typename Type>
int Search_tree<Type>::height() const {
	return root_node->height();
}

template <typename Type>
Type Search_tree<Type>::front() const {
	if (empty())
		throw underflow();
	

	return root_node->front()->node_value;
}

template <typename Type>
Type Search_tree<Type>::back() const {
	if (empty())
		throw underflow();

	return root_node->back()->node_value;
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::begin() {
	return empty() ? Iterator(this, back_sentinel) : Iterator(this, root_node->front());
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::end() {
	return Iterator(this, back_sentinel);
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::rbegin() {
	return empty() ? Iterator(this, front_sentinel) : Iterator(this, root_node->back());
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::rend() {
	return Iterator(this, front_sentinel);
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::find(Type const &obj) {
	if (empty())
		return Iterator(this, back_sentinel);

	typename Search_tree<Type>::Node *search_result = root_node->find(obj);

	if (search_result == nullptr)
		return Iterator(this, back_sentinel);
	else
		return Iterator(this, search_result);
}

template <typename Type>
void Search_tree<Type>::clear() {
	if (!empty()) {
		root_node->clear();
		root_node = nullptr;
		tree_size = 0;
	}

	// Reinitialize the sentinels
	front_sentinel->next_node = back_sentinel;
	back_sentinel->previous_node = front_sentinel;
}

template <typename Type>
bool Search_tree<Type>::insert(Type const &obj) {
	if (empty()) {
		root_node = new Search_tree::Node(obj);
		tree_size = 1;

		return true;
	} else if (root_node->insert(obj, root_node)) {
		++tree_size;
		return true;
	} else
		return false;
}

template <typename Type>
bool Search_tree<Type>::erase(Type const &obj) {
	if (!empty() && root_node->erase(obj, root_node)) {
		--tree_size;
		return true;
	} else
		return false;
}

template <typename Type>
Search_tree<Type>::Node::Node(Type const &obj) : node_value(obj),
						 left_tree(nullptr),
						 right_tree(nullptr),
						 next_node(nullptr),
						 previous_node(nullptr),
						 tree_height(0) {
}

template <typename Type>
void Search_tree<Type>::Node::update_height() {
	tree_height = std::max(left_tree->height(), right_tree->height()) + 1;
}

template <typename Type>
int Search_tree<Type>::Node::height() const {
	return (this == nullptr) ? -1 : tree_height;
}

template <typename Type>
bool Search_tree<Type>::Node::is_leaf() const {
	return ((left_tree == nullptr) && (right_tree == nullptr));
}

template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::front() {
	return (left_tree == nullptr) ? this : left_tree->front();
}

template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::back() {
	return (right_tree == nullptr) ? this : right_tree->back();
}

template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::find(Type const &obj) {
	if (obj == node_value) {
		return this;
	} else if (obj < node_value) {
		return (left_tree == nullptr) ? nullptr : left_tree->find(obj);
	} else {
		return (right_tree == nullptr) ? nullptr : right_tree->find(obj);
	}
}

template <typename Type>
void Search_tree<Type>::Node::clear() {
	if (left_tree != nullptr) {
		left_tree->clear();
	}

	if (right_tree != nullptr) {
		right_tree->clear();
	}

	delete this;
}

template <typename Type>
bool Search_tree<Type>::Node::insert(Type const &obj, Search_tree<Type>::Node *&to_this) {
	if (obj < node_value) {
		if (left_tree == nullptr) {
			left_tree = new Search_tree<Type>::Node(obj);
			update_height();

			return true;
		} else {
			if (left_tree->insert(obj, left_tree)) {
				update_height();
				return true;
			} else {
				return false;
			}
		}
	} else if (obj > node_value) {
		if (right_tree == nullptr) {
			right_tree = new Search_tree<Type>::Node(obj);
			update_height();

			return true;
		} else {
			if (right_tree->insert(obj, right_tree)) {
				update_height();
				return true;
			} else {
				return false;
			}
		}
	} else
		return false;
}

template <typename Type>
bool Search_tree<Type>::Node::erase(Type const &obj, Search_tree<Type>::Node *&to_this) {
	if (obj < node_value) {
		if (left_tree == nullptr)
			return false;
		else {
			if (left_tree->erase(obj, left_tree)) {
				update_height();
				return true;
			}
			return false;
		}
	} else if (obj > node_value) {
		if (right_tree == nullptr)
			return false;
		else {
			if (right_tree->erase(obj, right_tree)) {
				update_height();
				return true;
			}
			return false;
		}
	} else {
		assert(obj == node_value);
		if (is_leaf()) {
			to_this = nullptr;
			delete this;
		} else if (left_tree == nullptr) {
			to_this = right_tree;
			delete this;
		} else if (right_tree == nullptr) {
			to_this = left_tree;
			delete this;
		} else {
			node_value = right_tree->front()->node_value;
			right_tree->erase(node_value, right_tree);
			update_height();
		}
		return true;
	}
}

template <typename Type>
Search_tree<Type>::Iterator::Iterator(Search_tree<Type> *tree, typename Search_tree<Type>::Node *starting_node) : containing_tree(tree),
														  current_node(starting_node) {
}

template <typename Type>
Type Search_tree<Type>::Iterator::operator*() const {
	return current_node->node_value;
}

template <typename Type>
typename Search_tree<Type>::Iterator &Search_tree<Type>::Iterator::operator++() {
	return *this;
}

template <typename Type>
typename Search_tree<Type>::Iterator &Search_tree<Type>::Iterator::operator--() {
	return *this;
}

template <typename Type>
bool Search_tree<Type>::Iterator::operator==(typename Search_tree<Type>::Iterator const &rhs) const {
	return (current_node == rhs.current_node);
}

template <typename Type>
bool Search_tree<Type>::Iterator::operator!=(typename Search_tree<Type>::Iterator const &rhs) const {
	return (current_node != rhs.current_node);
}

template <typename T>
std::ostream &operator<<(std::ostream &out, Search_tree<T> const &list) {
	out << "not yet implemented";
	return out;
}

#endif
