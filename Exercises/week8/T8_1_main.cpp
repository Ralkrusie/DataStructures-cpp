/*
1. 二叉树镜像翻转
一、问题描述
给定一棵二叉树，将其镜像翻转（左右子树交换），然后输出翻转后的先序遍历序列。

二、输入形式
一行若干个整数，表示二叉树的先序遍历序列，空节点用-1表示。

三、输出形式
输出镜像翻转后的二叉树的先序遍历序列，空节点不输出。

四、样例输入

1 2 4 -1 -1 5 -1 -1 3 -1 6 -1 -1
五、样例输出

1 3 6 2 5 4
六、样例说明
原二叉树：

    1
   / \
  2   3
 / \   \
4   5   6
镜像翻转后：

    1
   / \
  3   2
 /   / \
6   5   4
先序遍历：1 3 6 2 5 4

七、评分标准
共10个测试用例。

八、类库使用要求
必须手动实现二叉树结构。
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

    void mirror() {
        mirrorNode(root);
    }

    void printPreOrder() const {
        bool first = true;
        printPreOrderNode(root, first);
        if (root != nullptr) {
            std::cout << '\n';
        }
    }

private:
    struct Node {
        int value;
        Node *left;
        Node *right;
        explicit Node(int x) : value(x), left(nullptr), right(nullptr) {}
    };

    static Node *buildNode(std::istream &in) {
        int value;
        if (!(in >> value) || value == -1) {
            return nullptr;
        }
        Node *node = new Node(value);
        node->left = buildNode(in);
        node->right = buildNode(in);
        return node;
    }

    static void mirrorNode(Node *current) {
        if (current == nullptr) {
            return;
        }
        Node *temp = current->left;
        current->left = current->right;
        current->right = temp;
        mirrorNode(current->left);
        mirrorNode(current->right);
    }

    static void printPreOrderNode(Node *current, bool &first) {
        if (current == nullptr) {
            return;
        }
        if (first) {
            std::cout << current->value;
            first = false;
        } else {
            std::cout << ' ' << current->value;
        }
        printPreOrderNode(current->left, first);
        printPreOrderNode(current->right, first);
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
    tree.mirror();
    tree.printPreOrder();
    return 0;
}
