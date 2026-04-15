/*
18. 单链表逆置-迭代法
单链表逆置-迭代法
一、问题描述
给定一个单链表，将其原地逆置。要求使用迭代法实现，空间复杂度为O(1)。

输入为先序遍历的链表节点值，-1表示链表结束（NULL）。

二、输入形式
一行若干个整数，表示链表节点值，以-1结束。

三、输出形式
输出逆置后的链表节点值，以空格分隔，最后不输出-1。

四、样例输入

1 2 3 4 5 -1
五、样例输出

5 4 3 2 1
六、样例说明
原链表：1 → 2 → 3 → 4 → 5 → NULL
逆置过程：

初始：prev = NULL, curr = 1

保存next = 2, 1->next = NULL, prev = 1, curr = 2

保存next = 3, 2->next = 1, prev = 2, curr = 3

继续直到curr = NULL

新头结点为prev = 5

逆置后：5 → 4 → 3 → 2 → 1 → NULL

七、评分标准
共6个测试用例。

八、类库使用要求
必须手动实现链表结构，禁止使用STL list。可以使用iostream。
*/
#include <iostream>

class myList {
public:
	myList() : headNode(nullptr), tailNode(nullptr), size(0) {}

	~myList() {
		clear();
	}

	void push_back(const int &x) {
		Node *newNode = new Node(x);
		if (headNode == nullptr) {
			headNode = tailNode = newNode;
		} else {
			tailNode->next = newNode;
			tailNode = newNode;
		}
		++size;
	}

	void reverseIterative() {
		Node *prev = nullptr;
		Node *current = headNode;
		tailNode = headNode;
		while (current != nullptr) {
			Node *next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		headNode = prev;
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

	void clear() {
		while (headNode != nullptr) {
			Node *next = headNode->next;
			delete headNode;
			headNode = next;
		}
		tailNode = nullptr;
		size = 0;
	}

private:
	struct Node {
		int value;
		Node *next;
		explicit Node(const int &v) : value(v), next(nullptr) {}
	};

	Node *headNode;
	Node *tailNode;
	size_t size;
};

int main() {
	myList list;
	int x;
	while (std::cin >> x && x != -1) {
		list.push_back(x);
	}
	list.reverseIterative();
	list.display();
	return 0;
}

