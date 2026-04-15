/*
15. 两个有序链表合并
两个有序链表合并
一、问题描述
将两个升序链表合并为一个新的升序链表。新链表是通过拼接给定的两个链表的所有节点组成的。

二、输入形式
两行输入，每行表示一个链表，节点值以空格分隔，以-1结束。

三、输出形式
输出合并后的有序链表节点值，用空格分隔。

四、样例输入

1 2 4 -1
1 3 4 -1
五、样例输出

1 1 2 3 4 4
六、样例说明
链表1：1 → 2 → 4
链表2：1 → 3 → 4
合并后：1 → 1 → 2 → 3 → 4 → 4

七、评分标准
共6个测试用例。

八、类库使用要求
必须手动实现链表结构。可以使用iostream。
*/
#include <iostream>

class myList {
public:
	myList() : headNode(nullptr), tailNode(nullptr), size(0) {}

	~myList() {
		clear();
	}

	myList(const myList &) = delete;
	myList &operator=(const myList &) = delete;

	myList(myList &&other) noexcept
		: headNode(other.headNode), tailNode(other.tailNode), size(other.size) {
		other.headNode = nullptr;
		other.tailNode = nullptr;
		other.size = 0;
	}

	myList &operator=(myList &&other) noexcept {
		if (this != &other) {
			clear();
			headNode = other.headNode;
			tailNode = other.tailNode;
			size = other.size;
			other.headNode = nullptr;
			other.tailNode = nullptr;
			other.size = 0;
		}
		return *this;
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

	static myList mergeSortedLists(myList &a, myList &b) {
		myList result;
		Node *left = a.headNode;
		Node *right = b.headNode;
		Node *tail = nullptr;

		while (left != nullptr && right != nullptr) {
			Node *current = nullptr;
			if (left->value <= right->value) {
				current = left;
				left = left->next;
			} else {
				current = right;
				right = right->next;
			}

			if (result.headNode == nullptr) {
				result.headNode = tail = current;
			} else {
				tail->next = current;
				tail = current;
			}
			++result.size;
		}

		Node *rest = (left != nullptr ? left : right);
		while (rest != nullptr) {
			Node *current = rest;
			rest = rest->next;
			if (result.headNode == nullptr) {
				result.headNode = tail = current;
			} else {
				tail->next = current;
				tail = current;
			}
			++result.size;
		}

		a.headNode = nullptr;
		a.tailNode = nullptr;
		a.size = 0;
		b.headNode = nullptr;
		b.tailNode = nullptr;
		b.size = 0;
		if (tail != nullptr) {
			tail->next = nullptr;
			result.tailNode = tail;
		}
		return result;
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
	myList list1;
	myList list2;
	int x;
	while (std::cin >> x && x != -1) {
		list1.push_back(x);
	}
	while (std::cin >> x && x != -1) {
		list2.push_back(x);
	}
	myList merged = myList::mergeSortedLists(list1, list2);
	merged.display();
	return 0;
}

