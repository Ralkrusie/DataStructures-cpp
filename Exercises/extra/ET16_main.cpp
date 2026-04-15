/*
16. 链表去重-保留重复
链表去重-保留重复
一、问题描述
给定一个已排序的链表，删除重复的元素，使得每个元素只出现一次，返回删除后链表的头节点。

二、输入形式
一行若干个整数，表示已排序链表节点值，以-1结束。

三、输出形式
输出去重后的链表节点值，用空格分隔。

四、样例输入

1 1 2 3 3 3 4 5 5 -1
五、样例输出

1 2 3 4 5
六、样例说明
原链表：1 → 1 → 2 → 3 → 3 → 3 → 4 → 5 → 5
去重后：1 → 2 → 3 → 4 → 5

七、评分标准
共6个测试用例。

八、类库使用要求
必须手动实现链表结构。要求原地修改，空间复杂度O(1)。可以使用iostream。
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

	void removeDuplicates() {
		Node *current = headNode;
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
		explicit Node(const int &x) : value(x), next(nullptr) {}
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
	list.removeDuplicates();
	list.display();
	return 0;
}

