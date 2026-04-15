#pragma once

#include <cstddef>
#include <iostream>
#include <type_traits>

template <typename T>
class myStack {
public:
	myStack() : topNode(nullptr), size(0) {}

	~myStack() {
		clear();
	}

	myStack(const myStack &) = delete;
	myStack &operator=(const myStack &) = delete;

	void push(const T &x) {
		Node *newNode = new Node(x);
		newNode->next = topNode;
		topNode = newNode;
		++size;
	}

	void pop() {
		if (isEmpty()) {
			return;
		}
		Node *oldTop = topNode;
		topNode = topNode->next;
		delete oldTop;
		--size;
	}

	T top() const {
		if (isEmpty()) {
			return T();
		}
		return topNode->value;
	}

	bool isEmpty() const {
		return size == 0;
	}

	size_t getSize() const {
		return size;
	}

	void clear() {
		while (topNode != nullptr) {
			Node *next = topNode->next;
			delete topNode;
			topNode = next;
		}
		size = 0;
	}

	void display() const {
		Node *current = topNode;
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

	void reverse() {
		Node *prev = nullptr;
		Node *current = topNode;
		while (current != nullptr) {
			Node *next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		topNode = prev;
	}

	T at(size_t index) const {
		if (index >= size) {
			return T();
		}
		Node *current = topNode;
		for (size_t i = 0; i < index; ++i) {
			current = current->next;
		}
		return current->value;
	}

	// 删除从栈顶开始的第 index 个结点（0 下标），用于按位置出栈题目。
	void popAt(size_t index) {
		if (index >= size) {
			return;
		}
		if (index == 0) {
			pop();
			return;
		}
		myStack helper;
		for (size_t i = 0; i < index; ++i) {
			helper.push(top());
			pop();
		}
		pop();
		for (size_t i = 0; i < index; ++i) {
			push(helper.top());
			helper.pop();
		}
	}

	template <typename U = T, typename std::enable_if<std::is_integral<U>::value, int>::type = 0>
	// 先按原顺序输出偶数，再按原顺序输出剩余奇数。
	void splitEvenOdd() {
		myStack evenStack;
		reverse();
		while (!isEmpty()) {
			if (top() % 2 == 0) {
				std::cout << top() << ' ';
			} else {
				evenStack.push(top());
			}
			pop();
		}
		std::cout << '\n';
		evenStack.reverse();
		evenStack.display();
	}

private:
	struct Node {
		T value;
		Node *next;
		explicit Node(const T &x) : value(x), next(nullptr) {}
	};

	Node *topNode;
	size_t size;
};
