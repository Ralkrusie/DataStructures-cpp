/*
1. 二叉树 —— 先序遍历输出分支节点
问题描述
给定一棵二叉树的括号字符串表示，请编写程序按先序遍历的顺序输出所有分支节点的值。

分支节点：有左孩子或右孩子（至少有一个非空子树）的节点。

二叉树括号字符串的格式规则如下：

每个节点用一个字符表示其值（本题限定为大写字母 A-Z）

若节点至少有一个非空子树，在节点值后紧跟括号 (...)

括号内为 左子树,右子树，左右子树之间用逗号分隔

若左子树为空而右子树非空，左子树位置用空内容表示，即 节点值(,右子树)

若右子树为空而左子树非空，仅写左子树，即 节点值(左子树)

空树用空字符串表示

输入形式
输入一行，表示二叉树结构的括号字符串，长度不超过 1000 个字符。节点值为大写字母 A-Z。

输出形式
输出一行字符串，表示按先序遍历顺序访问的所有分支节点的值（无空格）。

若为空树，输出空行。

样例输入
F(B(A,C),D(,E))
样例输出
FBD
样例说明
给定的二叉树结构如下：

        F
       / \
      B   D
     / \   \
    A   C   E
先序遍历顺序为：F → B → A → C → D → E。

其中分支节点（非叶子节点）为：

节点 F：左 B，右 D → 分支节点 ✓

节点 B：左 A，右 C → 分支节点 ✓

节点 D：左 #，右 E → 分支节点 ✓

节点 A：左 #，右 # → 叶子节点，不输出

节点 C：左 #，右 # → 叶子节点，不输出

节点 E：左 #，右 # → 叶子节点，不输出

按先序遍历顺序输出分支节点：FBD。

评分标准
本题目共 10 个测试用例。

类库使用要求
允许使用标准输入输出库（如 iostream、cstdio 等）

允许使用字符串处理库（如 cstring、string 等）

允许使用vector、stack、queue容器库。

需自行实现二叉树的节点结构与遍历逻辑

未按题意进行编码求解，扣减得分的50%
*/

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(int v): data(v) {}
};

Node* build(const string& str, int& p) {
    if (p >= str.size()) {
        return nullptr;
    }
    char ch = str[p];
    if (ch == ',' || ch == ')') {
        return nullptr;
    }

    Node* newNode = new Node(ch);
    p++;
    char nextCh = str[p];
    if (nextCh == '(') {
        //left:
        p++;
        if (str[p] == ',') {
            p++;
            newNode->left = nullptr;
        } else if (str[p] == ')') {
            newNode->left = nullptr;
        } else {
            newNode->left = build(str, p);
            p++;
        }

        //right:
        if (str[p] == ',') {
            p++;
        }
        if (str[p] == ')') {
            newNode->right = nullptr;
            p++;
        } else {
            newNode->right = build(str, p);
        }
    }
    return newNode;
}

void preOrder(Node* node) {
    if (!node) {
        return;
    }
    if (node->left || node->right) {
        cout << node->data;
    }
    if (node->left) {
        preOrder(node->left);
    }
    if (node->right) {
        preOrder(node->right);
    }
}


int main() {
    string line;
    getline(cin, line);
    if (line == "\0") {
        cout << endl;
        return 0;
    }
    // cout << line <<endl;
    int pos = 0;
    Node* root = build(line, pos);
    preOrder(root);
}
