#pragma once

#include <cstddef>
#include <iostream>
#include <type_traits>

template <typename T>
class myDoublyList {
public:
	myDoublyList() : headNode(nullptr), tailNode(nullptr), size(0) {}

	~myDoublyList() {
		clear();
	}

	myDoublyList(const myDoublyList &) = delete;
	myDoublyList &operator=(const myDoublyList &) = delete;

	void pushFront(const T &x) {
		Node *newNode = new Node(x);
		newNode->next = headNode;
		if (headNode != nullptr) {
			headNode->prev = newNode;
		} else {
			tailNode = newNode;
		}
		headNode = newNode;
		++size;
	}

	void pushBack(const T &x) {
		Node *newNode = new Node(x);
		newNode->prev = tailNode;
		if (tailNode != nullptr) {
			tailNode->next = newNode;
		} else {
			headNode = newNode;
		}
		tailNode = newNode;
		++size;
	}

	void popFront() {
		if (isEmpty()) {
			return;
		}
		Node *oldFront = headNode;
		headNode = headNode->next;
		if (headNode != nullptr) {
			headNode->prev = nullptr;
		} else {
			tailNode = nullptr;
		}
		delete oldFront;
		--size;
	}

	void popBack() {
		if (isEmpty()) {
			return;
		}
		Node *oldBack = tailNode;
		tailNode = tailNode->prev;
		if (tailNode != nullptr) {
			tailNode->next = nullptr;
		} else {
			headNode = nullptr;
		}
		delete oldBack;
		--size;
	}

	// Insert before the k-th node (1-based). If k == size + 1, append at tail.
	void insertAt(int k, const T &x) {
		if (k < 1 || static_cast<size_t>(k) > size + 1) {
			return;
		}
		if (k == 1) {
			pushFront(x);
			return;
		}
		if (static_cast<size_t>(k) == size + 1) {
			pushBack(x);
			return;
		}

		Node *current = headNode;
		for (int pos = 1; pos < k; ++pos) {
			current = current->next;
		}

		Node *newNode = new Node(x);
		newNode->prev = current->prev;
		newNode->next = current;
		current->prev->next = newNode;
		current->prev = newNode;
		++size;
	}

	// Delete the k-th node (1-based). Invalid k does nothing.
	void deleteAt(int k) {
		if (k < 1 || static_cast<size_t>(k) > size) {
			return;
		}
		if (k == 1) {
			popFront();
			return;
		}
		if (static_cast<size_t>(k) == size) {
			popBack();
			return;
		}

		Node *current = headNode;
		for (int pos = 1; pos < k; ++pos) {
			current = current->next;
		}

		Node *target = current;
		target->prev->next = target->next;
		target->next->prev = target->prev;
		delete target;
		--size;
	}

	T front() const {
		if (isEmpty()) {
			return T();
		}
		return headNode->value;
	}

	T back() const {
		if (isEmpty()) {
			return T();
		}
		return tailNode->value;
	}

	T at(size_t index) const {
		if (index >= size) {
			return T();
		}

		if (index < size / 2) {
			Node *current = headNode;
			for (size_t i = 0; i < index; ++i) {
				current = current->next;
			}
			return current->value;
		}

		Node *current = tailNode;
		for (size_t i = size - 1; i > index; --i) {
			current = current->prev;
		}
		return current->value;
	}

	bool isEmpty() const {
		return size == 0;
	}

	size_t getSize() const {
		return size;
	}

	void clear() {
		while (headNode != nullptr) {
			Node *next = headNode->next;
			delete headNode;
			headNode = next;
		}
		tailNode = nullptr;
		size = 0;
	}

	void displayForward() const {
		Node *current = headNode;
		if (current != nullptr) {
			std::cout << current->value;
			current = current->next;
			while (current != nullptr) {
				std::cout << ' ' << current->value;
				current = current->next;
			}
		}
		std::cout << '\n';
	}

	void displayBackward() const {
		Node *current = tailNode;
		if (current != nullptr) {
			std::cout << current->value;
			current = current->prev;
			while (current != nullptr) {
				std::cout << ' ' << current->value;
				current = current->prev;
			}
		}
		std::cout << '\n';
	}

	void displayEmpty() const {
		if (isEmpty()) {
			std::cout << "EMPTY\n";
			return;
		}
		displayForward();
	}

	template <typename U = T, typename std::enable_if<std::is_integral<U>::value, int>::type = 0>
	void createList(int n) {
		clear();
		for (int i = 1; i <= n; ++i) {
			pushBack(static_cast<T>(i));
		}
	}

private:
	struct Node {
		T value;
		Node *prev;
		Node *next;
		explicit Node(const T &x) : value(x), prev(nullptr), next(nullptr) {}
	};

	Node *headNode;
	Node *tailNode;
	size_t size;
};
