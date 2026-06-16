/*
2. 二叉树 —— 中序遍历
问题描述
给定一棵二叉树的节点信息表，请编写程序输出该二叉树的中序遍历序列（左子树 → 根节点 → 右子树）。

输入形式
第一行：一个整数 n（0 ≤ n ≤ 1000），表示二叉树的节点数。

接下来 n 行：每行输入一个节点的信息，格式为：

节点值 左子节点值 右子节点值
若左子节点或右子节点为空，则用字符 # 表示。

节点值为大写字母 A-Z，保证输入能构成一棵合法的树。

根节点确定方式：在所有节点中，未被任何节点作为左子节点或右子节点引用过的那个节点即为根节点。

输出形式
输出一行字符串，表示该二叉树的中序遍历序列（节点值按遍历顺序拼接，无空格）。

若为空树（n = 0），输出空行。

样例输入
9
A B C
B D E
C # F
D G H
E # #
F # I
G # #
H # #
I # #
样例输出
GDHBEACFI
样例说明
给定的二叉树结构如下：

        A
       / \
      B   C
     / \   \
    D   E   F
   / \       \
  G   H       I
中序遍历顺序为：G → D → H → B → E → A → C → F → I，拼接为字符串 GDHBEACFI。

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
#include <string>
#include <map>
#include <functional>

using namespace std;

struct Node {
    char data;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(char v): data(v) {}
};

void postOrder(Node* node) {
    if (node->left) { postOrder(node->left); }
    if (node->right) { postOrder(node->right); }
    if (!(node->left || node->right)) { cout << node->data; }
}

int main() {
    int n;
    cin >> n;
    map<char, Node*> temp;
    Node* root = nullptr;
    for (int i = 0; i < n; i++) {
        char ch;
        cin >> ch;
        if (temp.find(ch) == temp.end()) {
            root = new Node(ch);
            temp.emplace(ch, root);
        }
        Node* parent = temp[ch];

        //left
        cin >> ch;
        if (ch != '#') {
            if (temp.find(ch) == temp.end()) {
                temp.emplace(ch, new Node(ch));
            }
            parent->left = temp[ch];
        }

        //right
        cin >> ch;
        if (ch != '#') {
            if (temp.find(ch) == temp.end()) {
                temp.emplace(ch, new Node(ch));
            }
            parent->right = temp[ch];
        }   
    }
    if (root) { 
        postOrder(root);
        return 0;
    }
    cout << '\n';
    return 0;
}