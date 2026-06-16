/*
5. 第七章第6题
【问题描述】

假设二叉树采用二叉链存储结构存储，设计一个算法将二叉树bt1复制到二叉树bt2.


【输入形式】

输入为一棵二叉树的先序遍历序列（带空指针标记），其中：

非空结点用单个字符表示；

空指针（空子树）用 # 表示。


【输出形式】

输出复制后的二叉树的中序遍历结果（字符间用空格隔开，开头与末尾无多余空格）。若原树为空，输出为空。


【样例输入】

AB##C##


【样例输出】

B A C


【样例说明】

构建出原始二叉树 bt1；

将其完整复制为新的树 bt2；

对 bt2 进行中序遍历输出结果 B A C；

确保 bt1 与 bt2 是两个不同的内存树（复制而非引用）。


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

	myBinaryTree clone() const {
		myBinaryTree copied;
		copied.root = cloneNode(root);
		return copied;
	}

	void printInOrder() const {
		bool first = true;
		printInOrderNode(root, first);
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

	static Node *cloneNode(Node *current) {
		if (current == nullptr) {
			return nullptr;
		}
		Node *node = new Node(current->value);
		node->left = cloneNode(current->left);
		node->right = cloneNode(current->right);
		return node;
	}

	static void printInOrderNode(Node *current, bool &first) {
		if (current == nullptr) {
			return;
		}
		printInOrderNode(current->left, first);
		if (first) {
			std::cout << current->value;
			first = false;
		} else {
			std::cout << ' ' << current->value;
		}
		printInOrderNode(current->right, first);
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
	myBinaryTree bt1;
	bt1.build(std::cin);
	myBinaryTree bt2 = bt1.clone();
	bt2.printInOrder();
	return 0;
}