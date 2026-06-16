#pragma once

#include <cstddef>
#include <iostream>

class myString {
public:
	myString() : headNode('\0'), tailNode(&headNode), size(0) {}

	explicit myString(const char *cstr) : headNode('\0'), tailNode(&headNode), size(0) {
		assign(cstr);
	}

	~myString() {
		clear();
	}

	myString(const myString &) = delete;
	myString &operator=(const myString &) = delete;

	void pushBack(char ch) {
		Node *newNode = new Node(ch);
		tailNode->next = newNode;
		tailNode = newNode;
		++size;
	}

	void clear() {
		Node *current = headNode.next;
		while (current != nullptr) {
			Node *next = current->next;
			delete current;
			current = next;
		}
		headNode.next = nullptr;
		tailNode = &headNode;
		size = 0;
	}

	void assign(const char *cstr) {
		clear();
		append(cstr);
	}

	void append(const char *cstr) {
		if (cstr == nullptr) {
			return;
		}
		while (*cstr != '\0') {
			pushBack(*cstr);
			++cstr;
		}
	}

	void concat(myString &other) {
		if (other.isEmpty()) {
			return;
		}
		tailNode->next = other.headNode.next;
		tailNode = other.tailNode;
		size += other.size;

		other.headNode.next = nullptr;
		other.tailNode = &other.headNode;
		other.size = 0;
	}

	// 在第 k 个位置前插入字符（1 下标）；非法位置返回 false。
	bool insertAt(int k, char ch) {
		if (k < 1 || static_cast<size_t>(k) > size + 1) {
			return false;
		}
		Node *prev = &headNode;
		for (int pos = 1; pos < k; ++pos) {
			prev = prev->next;
		}
		Node *newNode = new Node(ch);
		newNode->next = prev->next;
		prev->next = newNode;
		if (prev == tailNode) {
			tailNode = newNode;
		}
		++size;
		return true;
	}

	// 删除第 k 个字符（1 下标）；非法位置返回 false。
	bool deleteAt(int k) {
		if (k < 1 || static_cast<size_t>(k) > size) {
			return false;
		}
		Node *prev = &headNode;
		for (int pos = 1; pos < k; ++pos) {
			prev = prev->next;
		}
		Node *target = prev->next;
		prev->next = target->next;
		if (target == tailNode) {
			tailNode = prev;
		}
		delete target;
		--size;
		return true;
	}

	// 返回第一次出现的位置（1 下标），不存在返回 -1。
	int findFirst(char ch) const {
		Node *current = headNode.next;
		int pos = 1;
		while (current != nullptr) {
			if (current->value == ch) {
				return pos;
			}
			current = current->next;
			++pos;
		}
		return -1;
	}

	char at(size_t index) const {
		if (index >= size) {
			return '\0';
		}
		Node *current = headNode.next;
		for (size_t i = 0; i < index; ++i) {
			current = current->next;
		}
		return current->value;
	}

	bool isEmpty() const {
		return size == 0;
	}

	size_t getSize() const {
		return size;
	}

	// 递归统计 pattern 在当前链串中的重叠出现次数。
	int countOverlapRecursive(const myString &pattern) const {
		if (pattern.isEmpty()) {
			return 0;
		}
		return countOverlapFrom(headNode.next, pattern.headNode.next);
	}

	void display() const {
		Node *current = headNode.next;
		while (current != nullptr) {
			std::cout << current->value;
			current = current->next;
		}
		std::cout << '\n';
	}

private:
	struct Node {
		char value;
		Node *next;
		explicit Node(char v) : value(v), next(nullptr) {}
	};

    // 从 textCurrent 和 patternCurrent 开始尝试匹配，成功返回 true；失败返回 false。
	static bool matchFrom(const Node *textCurrent, const Node *patternCurrent) {
		if (patternCurrent == nullptr) {
			return true;
		}
		if (textCurrent == nullptr) {
			return false;
		}
		if (textCurrent->value != patternCurrent->value) {
			return false;
		}
		return matchFrom(textCurrent->next, patternCurrent->next);
	}

    // 从 textStart 开始递归统计 pattern 的重叠出现次数。
	static int countOverlapFrom(const Node *textStart, const Node *patternHead) {
		if (textStart == nullptr) {
			return 0;
		}
		int current = matchFrom(textStart, patternHead) ? 1 : 0;
		return current + countOverlapFrom(textStart->next, patternHead);
	}

	Node headNode;
	Node *tailNode;
	size_t size;
};
