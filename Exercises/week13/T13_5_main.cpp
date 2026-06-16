/*

【问题描述】

使用输入构建一个二叉树，判断它是否是高度平衡的二叉树。本题中，一棵高度平衡二叉树定义为：一个二叉树每个节点的左右两个子树的高度差的绝对值不超过 1 。

【输入形式】

一行字符串，以完全二叉树的形式表示二叉树，节点用空格分开

【输出形式】

是平衡二叉树输出”True”，否则输出”False”

【样例输入一】

3 9 20 null null 15 7

【样例输出一】

True

【样例输入二】

1 2 2 3 3 null null 4 4

【样例输出二】

False

【样例说明】

测试数据的文件名为in.txt，输出文件名为out.txt

【评分标准】

该题目有10个测试用例，每通过一个测试用例得10分*/

#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(int v): data(v) {}
};

int height(Node* current) {
    if (!current) {
        return 0;
    }
    if (!current->left && !current->right) {
        return 1;
    }
    if (height(current->left) == -1 || height(current->right) == -1) {
        return -1;
    }
    int currentHeight = max(height(current->left), height(current->right)) + 1;
    int diff = abs(height(current->left) - height(current->right));
    return diff > 1 ? -1 : currentHeight;
}

int main() {
    ifstream fin("in.txt");
    vector<string> line;
    string node;
    while (fin >> node) {
        line.push_back(node);
    }
    fin.close();
    size_t lineSize = line.size();

    Node* root = new Node(stoi(line[0]));
    queue<pair<Node*, size_t>> qu;
    qu.push({root, 0});
    while (!qu.empty()) {
        auto current = qu.front();
        qu.pop();
        size_t leftIndex = 2 * current.second + 1;
        size_t rightIndex = 2 * current.second + 2;
        if (leftIndex < lineSize && line[leftIndex] != "null") {
            Node* leftNode = new Node(stoi(line[leftIndex]));
            current.first->left = leftNode;
            qu.push({leftNode, leftIndex});
        }
        if (rightIndex < lineSize && line[rightIndex] != "null") {
            Node* rightNode = new Node(stoi(line[rightIndex]));
            current.first->right = rightNode;
            qu.push({rightNode, rightIndex});
        }
    }
    
    ofstream fout("out.txt");
    if (height(root) == -1) {
        fout << "False\n";
        return 0;
    }
    fout << "True\n";
    return 0;
}