/*
2. 求二叉树深度高度
一、问题描述
给定一棵二叉树，计算树的深度（高度）。树的深度定义为从根节点到最远叶子节点的最长路径上的节点数。

二、输入形式
一行若干个整数，表示二叉树的先序遍历序列，空节点用-1表示。

三、输出形式
输出一个整数，表示二叉树的深度。

四、样例输入

1 2 4 -1 -1 5 -1 -1 3 -1 6 -1 -1
五、样例输出

3
六、样例说明
二叉树结构：

    1       (深度1)
   / \
  2   3     (深度2)
 / \   \
4   5   6   (深度3)
最大深度为3。

七、评分标准
共6个测试用例。

八、类库使用要求
必须手动实现二叉树结构，可以使用递归或迭代。
*/

#include <iostream>

template <typename T>
class myBinaryTree {
private:
    struct Node {
        T value;
        Node *leftNode;
        Node *rightNode;
        explicit Node(T &x) : value(x), leftNode(nullptr), rightNode(nullptr) {}
    };
    
    void clearNode(Node *current) {
        if (current == nullptr) {
            return;
        }
        clearNode(current->leftNode);
        clearNode(current->rightNode);
        size--;
        delete current;
    }

    size_t height(Node *current) const {
        if (current == nullptr) {
            return 0;
        }
        size_t leftHeight = height(current->leftNode);
		size_t rightHeight = height(current->rightNode);
		return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }

    Node *buildNode(std::istream &in) {
        T value;
        if (!(in >> value) || value == -1) {
            return nullptr;
        }
        Node *newNode = new Node(value);
        newNode->leftNode = buildNode(in);
        newNode->rightNode = buildNode(in);
        size++;
        return newNode;
    }

    Node *rootNode;
    size_t size;

public:
    myBinaryTree() : rootNode(nullptr), size(0) {}

    ~myBinaryTree() {
        clearNode(rootNode);
    }

    bool isEmpty() const {
        return size == 0;
    }

    size_t getSize() const {
		return size;
	}

    size_t height() const {
		return height(rootNode);
	}

    void build(std::istream &in) {
        clearNode(rootNode);
        rootNode = buildNode(in);
    }

};

int main() {
    myBinaryTree<int> tree;
    tree.build(std::cin);
    size_t height = tree.height();
    std::cout << height << std::endl;
    return 0;
}
