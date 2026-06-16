#pragma once

#include <cstddef>
#include <iostream>
#include <queue>

template <typename T>
class myBinaryTree {
public:
	myBinaryTree() : rootNode(nullptr), size(0) {}

	~myBinaryTree() {
		clear();
	}

	myBinaryTree(const myBinaryTree &) = delete;
	myBinaryTree &operator=(const myBinaryTree &) = delete;

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

	void setRoot(const T &x) {
		clear();
		rootNode = new Node(x);
		size = 1;
	}

	T getRoot() const {
		if (rootNode == nullptr) {
			return T();
		}
		return rootNode->value;
	}

	bool contains(const T &x) const {
		return findNode(rootNode, x) != nullptr;
	}

	void insertLeft(const T &parent, const T &x) {
		Node *targetParent = findNode(rootNode, parent);
		if (targetParent == nullptr || targetParent->leftNode != nullptr) {
			return;
		}
		targetParent->leftNode = new Node(x);
		++size;
	}

	void insertRight(const T &parent, const T &x) {
		Node *targetParent = findNode(rootNode, parent);
		if (targetParent == nullptr || targetParent->rightNode != nullptr) {
			return;
		}
		targetParent->rightNode = new Node(x);
		++size;
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
		if (current == nullptr) {
			return nullptr;
		}
		if (current->value == x) {
			return current;
		}
		Node *found = findNode(current->leftNode, x);
		if (found != nullptr) {
			return found;
		}
		return findNode(current->rightNode, x);
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