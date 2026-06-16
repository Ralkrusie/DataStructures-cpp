/*
6. 第七章第5题
【问题描述】

假设二叉树采用二叉链存储结构，设计一个算法判断一棵二叉树bt是否对称。所谓对称，是指其左、右子树的结构是对称的。


【输入形式】

输入为该二叉树的先序遍历序列（带空指针标记），其中空子树用 # 表示，非空结点用单个字符表示。


【输出形式】

若该二叉树对称，输出Yes；否则输出No。


【样例输入】

AB##B##


【样例输出】

Yes


【样例说明】



该树的结构如下：

    A

   / \

  B   B

左右子树完全对称，节点值也一致，因此输出 Yes。
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

  bool isSymmetric() const {
    if (root == nullptr) {
      return true;
    }
    return isMirror(root->left, root->right);
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

  static bool isMirror(Node *leftNode, Node *rightNode) {
    if (leftNode == nullptr && rightNode == nullptr) {
      return true;
    }
    if (leftNode == nullptr || rightNode == nullptr) {
      return false;
    }
    if (leftNode->value != rightNode->value) {
      return false;
    }
    return isMirror(leftNode->left, rightNode->right) &&
         isMirror(leftNode->right, rightNode->left);
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
  std::cout << (tree.isSymmetric() ? "Yes" : "No") << '\n';
  return 0;
}