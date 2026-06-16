#pragma once

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <queue>

template <typename T>
class myAVLTree {
public:
	myAVLTree() : rootNode(nullptr), size(0) {}

	~myAVLTree() {
		clear();
	}

	myAVLTree(const myAVLTree &) = delete;
	myAVLTree &operator=(const myAVLTree &) = delete;

	myAVLTree(myAVLTree &&other) noexcept
		: rootNode(nullptr), size(0) {
		moveFrom(other);
	}

	myAVLTree &operator=(myAVLTree &&other) noexcept {
		if (this != &other) {
			clear();
			moveFrom(other);
		}
		return *this;
	}

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

	T getRoot() const {
		if (rootNode == nullptr) {
			return T();
		}
		return rootNode->value;
	}

	bool contains(const T &x) const {
		return contains(rootNode, x);
	}

	bool search(const T &x) const {
		return contains(x);
	}

	void insert(const T &x) {
		bool inserted = false;
		rootNode = insert(rootNode, x, inserted);
		if (inserted) {
			++size;
		}
	}

	void remove(const T &x) {
		bool removed = false;
		rootNode = remove(rootNode, x, removed);
		if (removed) {
			--size;
		}
	}

	void erase(const T &x) {
		remove(x);
	}

	void display() const {
		displayLevelOrder();
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
		int nodeHeight;

		explicit Node(const T &x)
			: value(x), leftNode(nullptr), rightNode(nullptr), nodeHeight(1) {}
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
		return current == nullptr ? 0u : static_cast<size_t>(current->nodeHeight);
	}

	static int nodeHeight(Node *current) {
		return current == nullptr ? 0 : current->nodeHeight;
	}

	static void updateHeight(Node *current) {
		current->nodeHeight = std::max(nodeHeight(current->leftNode), nodeHeight(current->rightNode)) + 1;
	}

	static int balanceFactor(Node *current) {
		return current == nullptr ? 0 : nodeHeight(current->leftNode) - nodeHeight(current->rightNode);
	}

	static Node *rotateRight(Node *current) {
		Node *newRoot = current->leftNode;
		Node *transfer = newRoot->rightNode;
		newRoot->rightNode = current;
		current->leftNode = transfer;
		updateHeight(current);
		updateHeight(newRoot);
		return newRoot;
	}

	static Node *rotateLeft(Node *current) {
		Node *newRoot = current->rightNode;
		Node *transfer = newRoot->leftNode;
		newRoot->leftNode = current;
		current->rightNode = transfer;
		updateHeight(current);
		updateHeight(newRoot);
		return newRoot;
	}

	static Node *rebalance(Node *current) {
		updateHeight(current);
		int factor = balanceFactor(current);
		if (factor > 1) {
			if (balanceFactor(current->leftNode) < 0) {
				current->leftNode = rotateLeft(current->leftNode);
			}
			return rotateRight(current);
		}
		if (factor < -1) {
			if (balanceFactor(current->rightNode) > 0) {
				current->rightNode = rotateRight(current->rightNode);
			}
			return rotateLeft(current);
		}
		return current;
	}

	static Node *insert(Node *current, const T &x, bool &inserted) {
		if (current == nullptr) {
			inserted = true;
			return new Node(x);
		}
		if (x < current->value) {
			current->leftNode = insert(current->leftNode, x, inserted);
		} else if (current->value < x) {
			current->rightNode = insert(current->rightNode, x, inserted);
		} else {
			return current;
		}
		return rebalance(current);
	}

	static Node *minNode(Node *current) {
		while (current != nullptr && current->leftNode != nullptr) {
			current = current->leftNode;
		}
		return current;
	}

	static Node *remove(Node *current, const T &x, bool &removed) {
		if (current == nullptr) {
			return nullptr;
		}
		if (x < current->value) {
			current->leftNode = remove(current->leftNode, x, removed);
		} else if (current->value < x) {
			current->rightNode = remove(current->rightNode, x, removed);
		} else {
			removed = true;
			if (current->leftNode == nullptr || current->rightNode == nullptr) {
				Node *child = (current->leftNode != nullptr) ? current->leftNode : current->rightNode;
				delete current;
				return child;
			}
			Node *successor = minNode(current->rightNode);
			current->value = successor->value;
			bool dummy = false;
			current->rightNode = remove(current->rightNode, successor->value, dummy);
		}
		return rebalance(current);
	}

	static bool contains(Node *current, const T &x) {
		if (current == nullptr) {
			return false;
		}
		if (x < current->value) {
			return contains(current->leftNode, x);
		}
		if (current->value < x) {
			return contains(current->rightNode, x);
		}
		return true;
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

	void moveFrom(myAVLTree<T> &other) {
		rootNode = other.rootNode;
		size = other.size;
		other.rootNode = nullptr;
		other.size = 0;
	}

	Node *rootNode;
	size_t size;
};
