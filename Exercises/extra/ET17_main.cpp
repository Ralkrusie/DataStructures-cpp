/*
17. 链表分区-奇偶分离
链表分区-奇偶分离
一、问题描述
给定一个单链表，将所有奇数位置的节点和偶数位置的节点分别连接在一起，然后返回重新组合的链表。

注意：这里的奇偶指的是节点的位置，而不是节点的值。

二、输入形式
一行若干个整数，表示链表节点值，以-1结束。

三、输出形式
输出重新组合后的链表节点值，奇数位置节点在前，偶数位置节点在后，用空格分隔。

四、样例输入

1 2 3 4 5 -1
五、样例输出

1 3 5 2 4
六、样例说明
原链表：1(位置1) → 2(位置2) → 3(位置3) → 4(位置4) → 5(位置5)

奇数位置节点：1 → 3 → 5

偶数位置节点：2 → 4

重组后：1 → 3 → 5 → 2 → 4

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

	void oddEvenReorder() {
		if (headNode == nullptr || headNode->next == nullptr) {
			return;
		}

		Node *odd = headNode;
		Node *evenHead = headNode->next;
		Node *even = evenHead;

		while (even != nullptr && even->next != nullptr) {
			odd->next = even->next;
			odd = odd->next;
			even->next = odd->next;
			even = even->next;
		}

		odd->next = evenHead;
		tailNode = even == nullptr ? odd : even;
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
	list.oddEvenReorder();
	list.display();
	return 0;
}

