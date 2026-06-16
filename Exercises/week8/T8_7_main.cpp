/*
7. 第七章第4题
【问题描述】

假设二叉树中的每个结点值为单个字符，采用二叉链存储结构存储。设计一个算法按从右到左的次序输出一棵二叉树bt中的所有叶子结点。


【输入形式】

输入为二叉树的先序遍历序列（带空指针标记），其中空子树用 # 表示，非空结点用单个字符表示。



【输出形式】

从右到左输出所有叶子结点的值，空格分隔；若树为空，则无输出。


【样例输入】

ABD##E##CF###


【样例输出】

F E D


【样例说明】

叶子结点为 D, E, F ，从右到左的次序为 F→E→D


*/

#include <iostream>

class myBinaryTree {
public:
	myBinaryTree() : root(nullptr) {}

	~myBinaryTree() {
		clearNode(root);
	}

	void build(std::istream &in) {
		clearNode(root);
		root = buildNode(in);
	}

	void printLeavesRightToLeft() const {
		bool first = true;
		printLeavesNode(root, first);
		if (!first) {
			std::cout << '\n';
		}
	}

private:
	struct Node {
		char value;
		Node *left;
		Node *right;
		explicit Node(char x) : value(x), left(nullptr), right(nullptr) {}
	};

	static Node *buildNode(std::istream &in) {
		char ch;
		if (!(in >> ch) || ch == '#') {
			return nullptr;
		}
		Node *node = new Node(ch);
		node->left = buildNode(in);
		node->right = buildNode(in);
		return node;
	}

	static void printLeavesNode(Node *current, bool &first) {
		if (current == nullptr) {
			return;
		}
		if (current->left == nullptr && current->right == nullptr) {
			if (first) {
				std::cout << current->value;
				first = false;
			} else {
				std::cout << ' ' << current->value;
			}
			return;
		}
		printLeavesNode(current->right, first);
		printLeavesNode(current->left, first);
	}

	static void clearNode(Node *current) {
		if (current == nullptr) {
			return;
		}
		clearNode(current->left);
		clearNode(current->right);
		delete current;
	}

	Node *root;
};

int main() {
	myBinaryTree tree;
	tree.build(std::cin);
	tree.printLeavesRightToLeft();
	return 0;
}