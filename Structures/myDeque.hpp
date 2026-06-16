#pragma once

#include <cstddef>
#include <iostream>

template <typename T>
class myDeque {
public:
	myDeque() : headNode(nullptr), tailNode(nullptr), size(0) {}

	~myDeque() {
		clear();
	}

	myDeque(const myDeque &) = delete;
	myDeque &operator=(const myDeque &) = delete;

	void pushFront(const T &x) {
		Node *newNode = new Node(x);
		newNode->next = headNode;
		if (headNode != nullptr) {
			headNode->prev = newNode;
		}
		headNode = newNode;
		if (tailNode == nullptr) {
			tailNode = newNode;
		}
		++size;
	}

	void pushBack(const T &x) {
		Node *newNode = new Node(x);
		newNode->prev = tailNode;
		if (tailNode != nullptr) {
			tailNode->next = newNode;
		}
		tailNode = newNode;
		if (headNode == nullptr) {
			headNode = newNode;
		}
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

	void display() const {
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

	// 空双端队列时输出 EMPTY，适配对应题目的输出要求。
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
		Node *prev;
		Node *next;
		explicit Node(const T &x) : value(x), prev(nullptr), next(nullptr) {}
	};

	Node *headNode;
	Node *tailNode;
	size_t size;
};
