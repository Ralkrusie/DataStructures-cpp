#pragma once

#include <cstddef>
#include <iostream>
#include <type_traits>

template <typename T>
class myList {
public:
	myList() : headNode(T()), tailNode(&headNode), size(0) {}

	~myList() {
		clear();
	}

	myList(const myList &) = delete;
	myList &operator=(const myList &) = delete;

	myList(myList &&other) noexcept
		: headNode(T()), tailNode(&headNode), size(0) {
		moveFrom(other);
	}

	myList &operator=(myList &&other) noexcept {
		if (this != &other) {
			clear();
			moveFrom(other);
		}
		return *this;
	}

	void pushBack(const T &x) {
		Node *node = new Node(x);
		tailNode->next = node;
		tailNode = node;
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

	size_t getSize() const {
		return size;
	}

	bool isEmpty() const {
		return size == 0;
	}

	// 按 1..n 创建链表，供命令式创建题使用。
	template <typename U = T, typename std::enable_if<std::is_integral<U>::value, int>::type = 0>
	void createList(int n) {
		clear();
		for (int i = 1; i <= n; ++i) {
			pushBack(static_cast<T>(i));
		}
	}

	void insertAt(int k, const T &x) {
		if (k < 1 || static_cast<size_t>(k) > size + 1) {
			return;
		}
		Node *prev = &headNode;
		for (int pos = 1; pos < k; ++pos) {
			prev = prev->next;
		}
		Node *node = new Node(x);
		node->next = prev->next;
		prev->next = node;
		if (prev == tailNode) {
			tailNode = node;
		}
		++size;
	}

	void deleteAt(int k) {
		if (k < 1 || static_cast<size_t>(k) > size) {
			return;
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
	}

	void display() const {
		if (headNode.next == nullptr) {
			std::cout << '\n';
			return;
		}
		Node *current = headNode.next;
		std::cout << current->value;
		current = current->next;
		while (current != nullptr) {
			std::cout << ' ' << current->value;
			current = current->next;
		}
		std::cout << '\n';
	}

	// 空链表时输出 EMPTY，适配对应题目的输出要求。
	void displayEmpty() const {
		if (headNode.next == nullptr) {
			std::cout << "EMPTY\n";
			return;
		}
		display();
	}

	// 对有序链表做原地去重。
	void removeDuplicates() {
		Node *current = headNode.next;
		while (current != nullptr && current->next != nullptr) {
			if (current->value == current->next->value) {
				Node *dup = current->next;
				current->next = dup->next;
				if (dup == tailNode) {
					tailNode = current;
				}
				delete dup;
				--size;
			} else {
				current = current->next;
			}
		}
		if (headNode.next == nullptr) {
			tailNode = &headNode;
		}
	}

	// 按位置奇偶重排：奇数位在前，偶数位在后。
	void oddEvenReorder() {
		if (headNode.next == nullptr || headNode.next->next == nullptr) {
			return;
		}

		Node *odd = headNode.next;
		Node *evenHead = odd->next;
		Node *even = evenHead;
		Node *lastEven = evenHead;

		while (even != nullptr && even->next != nullptr) {
			lastEven = even;
			odd->next = even->next;
			odd = odd->next;
			even->next = odd->next;
			even = even->next;
		}

		odd->next = evenHead;
		tailNode = lastEven;
	}

	void reverseIterative() {
		Node *current = headNode.next;
		if (current == nullptr || current->next == nullptr) {
			return;
		}
		Node *oldFirst = current;
		Node *prev = nullptr;
		while (current != nullptr) {
			Node *next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		headNode.next = prev;
		tailNode = oldFirst;
	}

	void reverseRecursive() {
		Node *first = headNode.next;
		if (first == nullptr || first->next == nullptr) {
			return;
		}
		headNode.next = reverseNodes(first);
		tailNode = first;
	}

	// 快慢指针查找倒数第 k 个结点，非法时返回默认值 T()。
	T kthFromEnd(int k) const {
		if (k <= 0 || static_cast<size_t>(k) > size) {
			return T();
		}
		Node *fast = headNode.next;
		for (int i = 0; i < k; ++i) {
			fast = fast->next;
		}
		Node *slow = headNode.next;
		while (fast != nullptr) {
			slow = slow->next;
			fast = fast->next;
		}
		return slow->value;
	}

	// 通过重连已有结点合并两个有序链表；合并后源链表清空。
	static myList<T> mergeSortedLists(myList<T> &a, myList<T> &b) {
		myList<T> result;
		Node *left = a.headNode.next;
		Node *right = b.headNode.next;
		Node *tail = &result.headNode;

		while (left != nullptr && right != nullptr) {
			if (left->value <= right->value) {
				tail->next = left;
				left = left->next;
			} else {
				tail->next = right;
				right = right->next;
			}
			tail = tail->next;
			++result.size;
		}

		Node *rest = (left != nullptr ? left : right);
		while (rest != nullptr) {
			tail->next = rest;
			tail = tail->next;
			rest = rest->next;
			++result.size;
		}

		if (result.size == 0) {
			result.tailNode = &result.headNode;
		} else {
			tail->next = nullptr;
			result.tailNode = tail;
		}

		a.headNode.next = nullptr;
		a.tailNode = &a.headNode;
		a.size = 0;
		b.headNode.next = nullptr;
		b.tailNode = &b.headNode;
		b.size = 0;
		return result;
	}

private:
	struct Node {
		T value;
		Node *next;
		explicit Node(const T &v = T()) : value(v), next(nullptr) {}
	};

	static Node *reverseNodes(Node *head) {
		if (head == nullptr || head->next == nullptr) {
			return head;
		}
		Node *newHead = reverseNodes(head->next);
		head->next->next = head;
		head->next = nullptr;
		return newHead;
	}

	void moveFrom(myList<T> &other) {
		if (other.headNode.next == nullptr) {
			return;
		}
		headNode.next = other.headNode.next;
		tailNode = other.tailNode;
		size = other.size;
		other.headNode.next = nullptr;
		other.tailNode = &other.headNode;
		other.size = 0;
	}

	Node headNode;
	Node *tailNode;
	size_t size;
};
