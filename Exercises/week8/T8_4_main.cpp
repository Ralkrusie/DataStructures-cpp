/*
4. 二叉树的创建与遍历
一、问题描述
根据给定的先序遍历序列创建二叉树（空节点用-1表示），然后输出中序、后序和层序遍历序列。

二、输入形式
一行若干个整数，表示二叉树的先序遍历序列，空节点用-1表示。

三、输出形式
输出三行，分别是中序、后序和层序遍历序列，节点值用空格分隔。

四、样例输入

1 2 4 -1 -1 5 -1 -1 3 -1 6 -1 -1
五、样例输出

4 2 5 1 3 6
4 5 2 6 3 1
1 2 3 4 5 6
六、样例说明
二叉树结构：

    1
   / \
  2   3
 / \   \
4   5   6
七、评分标准
共8个测试用例。

八、类库使用要求
必须手动实现二叉树结构和遍历算法，可以使用queue。
*/

#include <iostream>
#include <queue>

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

    void printInOrder() const {
        bool first = true;
        printInOrderNode(root, first);
        std::cout << '\n';
    }

    void printPostOrder() const {
        bool first = true;
        printPostOrderNode(root, first);
        std::cout << '\n';
    }

    void printLevelOrder() const {
        bool first = true;
        std::queue<Node *> q;
        if (root != nullptr) {
            q.push(root);
        }
        while (!q.empty()) {
            Node *current = q.front();
            q.pop();
            printValue(current->value, first);
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        std::cout << '\n';
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

    static void printValue(int x, bool &first) {
        if (first) {
            std::cout << x;
            first = false;
        } else {
            std::cout << ' ' << x;
        }
    }

    static void printInOrderNode(Node *current, bool &first) {
        if (current == nullptr) {
            return;
        }
        printInOrderNode(current->left, first);
        printValue(current->value, first);
        printInOrderNode(current->right, first);
    }

    static void printPostOrderNode(Node *current, bool &first) {
        if (current == nullptr) {
            return;
        }
        printPostOrderNode(current->left, first);
        printPostOrderNode(current->right, first);
        printValue(current->value, first);
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
    tree.printInOrder();
    tree.printPostOrder();
    tree.printLevelOrder();
    return 0;
}