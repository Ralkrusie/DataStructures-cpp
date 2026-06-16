/*
3. 求二叉树叶子节点数
一、问题描述
给定一棵二叉树，计算树中叶子节点（度为0的节点）的数量。

二、输入形式
一行若干个整数，表示二叉树的先序遍历序列，空节点用-1表示。

三、输出形式
输出一个整数，表示二叉树的叶子节点数。

四、样例输入

1 2 4 -1 -1 5 -1 -1 3 -1 6 -1 -1
五、样例输出

3
六、样例说明
二叉树结构：

    1
   / \
  2   3
 / \   \
4   5   6
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

    int leafCount() const {
        return leafCountNode(root);
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

    static int leafCountNode(Node *current) {
        if (current == nullptr) {
            return 0;
        }
        if (current->left == nullptr && current->right == nullptr) {
            return 1;
        }
        return leafCountNode(current->left) + leafCountNode(current->right);
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
    std::cout << tree.leafCount() << '\n';
    return 0;
}