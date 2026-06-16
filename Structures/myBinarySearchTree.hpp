#pragma once

#include <cstddef>
#include <iostream>
#include <queue>

template <typename T>
class myBinarySearchTree {
public:
	myBinarySearchTree() : rootNode(nullptr), size(0) {}

	~myBinarySearchTree() {
		clear();
	}

	myBinarySearchTree(const myBinarySearchTree &) = delete;
	myBinarySearchTree &operator=(const myBinarySearchTree &) = delete;

	void clear() {
		clear(rootNode);
		rootNode = nullptr;
		size = 0;
	}

	bool isEmpty() const {
		return size == 0;
	}

	size_t getSize() const {
		return size;
	}

	size_t height() const {
		return height(rootNode);
	}

	void insert(const T &x) {
		if (insert(rootNode, x)) {
			++size;
		}
	}

	void remove(const T &x) {
		if (remove(rootNode, x)) {
			--size;
		}
	}

	bool contains(const T &x) const {
		return findNode(rootNode, x) != nullptr;
	}

	T getMin() const {
		Node *node = minimum(rootNode);
		if (node == nullptr) {
			return T();
		}
		return node->value;
	}

	T getMax() const {
		Node *node = maximum(rootNode);
		if (node == nullptr) {
			return T();
		}
		return node->value;
	}

	T getRoot() const {
		if (rootNode == nullptr) {
			return T();
		}
		return rootNode->value;
	}

	void display() const {
		displayInOrder();
	}

	void displayPreOrder() const {
		bool first = true;
		displayPreOrder(rootNode, first);
		std::cout << '\n';
	}

	void displayInOrder() const {
		bool first = true;
		displayInOrder(rootNode, first);
		std::cout << '\n';
	}

	void displayPostOrder() const {
		bool first = true;
		displayPostOrder(rootNode, first);
		std::cout << '\n';
	}

	void displayLevelOrder() const {
		std::queue<Node *> nodeQueue;
		if (rootNode != nullptr) {
			nodeQueue.push(rootNode);
		}
		bool first = true;
		while (!nodeQueue.empty()) {
			Node *current = nodeQueue.front();
			nodeQueue.pop();
			displayValue(current->value, first);
			if (current->leftNode != nullptr) {
				nodeQueue.push(current->leftNode);
			}
			if (current->rightNode != nullptr) {
				nodeQueue.push(current->rightNode);
			}
		}
		std::cout << '\n';
	}

	void displayEmpty() const {
		if (isEmpty()) {
			std::cout << "EMPTY\n";
			return;
		}
		display();
	}

private:
	struct Node {
		T value;
		Node *leftNode;
		Node *rightNode;
		explicit Node(const T &x) : value(x), leftNode(nullptr), rightNode(nullptr) {}
	};

	static void clear(Node *current) {
		if (current == nullptr) {
			return;
		}
		clear(current->leftNode);
		clear(current->rightNode);
		delete current;
	}

	static size_t height(Node *current) {
		if (current == nullptr) {
			return 0;
		}
		size_t leftHeight = height(current->leftNode);
		size_t rightHeight = height(current->rightNode);
		return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
	}

	static Node *findNode(Node *current, const T &x) {
		while (current != nullptr) {
			if (x < current->value) {
				current = current->leftNode;
			} else if (current->value < x) {
				current = current->rightNode;
			} else {
				return current;
			}
		}
		return nullptr;
	}

	static Node *minimum(Node *current) {
		if (current == nullptr) {
			return nullptr;
		}
		while (current->leftNode != nullptr) {
			current = current->leftNode;
		}
		return current;
	}

	static Node *maximum(Node *current) {
		if (current == nullptr) {
			return nullptr;
		}
		while (current->rightNode != nullptr) {
			current = current->rightNode;
		}
		return current;
	}

	static bool insert(Node *&current, const T &x) {
		if (current == nullptr) {
			current = new Node(x);
			return true;
		}
		if (x < current->value) {
			return insert(current->leftNode, x);
		}
		if (current->value < x) {
			return insert(current->rightNode, x);
		}
		return false;
	}

	static bool remove(Node *&current, const T &x) {
		if (current == nullptr) {
			return false;
		}
		if (x < current->value) {
			return remove(current->leftNode, x);
		}
		if (current->value < x) {
			return remove(current->rightNode, x);
		}

		if (current->leftNode == nullptr) {
			Node *target = current;
			current = current->rightNode;
			delete target;
			return true;
		}
		if (current->rightNode == nullptr) {
			Node *target = current;
			current = current->leftNode;
			delete target;
			return true;
		}

		Node *successor = minimum(current->rightNode);
		current->value = successor->value;
		return remove(current->rightNode, successor->value);
	}

	static void displayValue(const T &x, bool &first) {
		if (first) {
			std::cout << x;
			first = false;
		} else {
			std::cout << ' ' << x;
		}
	}

	static void displayPreOrder(Node *current, bool &first) {
		if (current == nullptr) {
			return;
		}
		displayValue(current->value, first);
		displayPreOrder(current->leftNode, first);
		displayPreOrder(current->rightNode, first);
	}

	static void displayInOrder(Node *current, bool &first) {
		if (current == nullptr) {
			return;
		}
		displayInOrder(current->leftNode, first);
		displayValue(current->value, first);
		displayInOrder(current->rightNode, first);
	}

	static void displayPostOrder(Node *current, bool &first) {
		if (current == nullptr) {
			return;
		}
		displayPostOrder(current->leftNode, first);
		displayPostOrder(current->rightNode, first);
		displayValue(current->value, first);
	}

	Node *rootNode;
	size_t size;
};