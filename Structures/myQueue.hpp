#pragma once

#include <cstddef>
#include <iostream>

template <typename T>
class myQueue {
public:
	myQueue() : headNode(nullptr), tailNode(nullptr), size(0) {}

	~myQueue() {
		clear();
	}

	myQueue(const myQueue &) = delete;
	myQueue &operator=(const myQueue &) = delete;

	void push(const T &x) {
		Node *newNode = new Node(x);
		if (tailNode == nullptr) {
			headNode = tailNode = newNode;
		} else {
			tailNode->next = newNode;
			tailNode = newNode;
		}
		++size;
	}

	void pop() {
		if (isEmpty()) {
			return;
		}
		Node *oldHead = headNode;
		headNode = headNode->next;
		delete oldHead;
		--size;
		if (headNode == nullptr) {
			tailNode = nullptr;
		}
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

	// 空队列时输出 EMPTY，适配对应题目的输出要求。
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
		Node *next;
		explicit Node(const T &x) : value(x), next(nullptr) {}
	};

	Node *headNode;
	Node *tailNode;
	size_t size;
};
