/*
【问题描述】

    假设二叉树中的每个结点值为单个整数，采用二叉链结构存储，设计算法判断给定的二叉树是否是完全二叉树。假定每棵二叉树节点不超过2000个。

【输入形式】

    每个测试是一颗二叉树的括号表示法字符串

【输出形式】

     如果是完全二叉树，输出“1”；如果不是完全二叉树，输出“0”

【样例输入】

    1(2(4,5),3)

【样例输出】

     1

【样例说明】

   测试数据的文件名为in.txt                                            
*/

#include <iostream>
#include <string>
#include <queue>
#include <cctype>
#include <fstream>
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// 递归解析：支持多位数与负数，允许空子树表示为"(,x)" 或 "(x,)"
TreeNode* parseNode(const std::string& s, int& pos) {
    int n = (int)s.size();
    while (pos < n && isspace((unsigned char)s[pos])) ++pos;
    if (pos >= n) return nullptr;
    if (s[pos] == ')' || s[pos] == ',') return nullptr; // 空子树

    // 解析整数
    int sign = 1;
    if (s[pos] == '+') { ++pos; }
    else if (s[pos] == '-') { sign = -1; ++pos; }
    if (pos >= n || !isdigit((unsigned char)s[pos])) return nullptr;
    long long val = 0;
    while (pos < n && isdigit((unsigned char)s[pos])) {
        val = val * 10 + (s[pos] - '0');
        ++pos;
    }
    TreeNode* node = new TreeNode((int)(val * sign));

    while (pos < n && isspace((unsigned char)s[pos])) ++pos;
    if (pos < n && s[pos] == '(') {
        ++pos; // consume '('
        // left child (可能为空)
        TreeNode* left = nullptr;
        if (pos < n && s[pos] != ',') left = parseNode(s, pos);
        while (pos < n && isspace((unsigned char)s[pos])) ++pos;
        if (pos < n && s[pos] == ',') ++pos; // consume ','
        // right child (可能为空)
        TreeNode* right = nullptr;
        if (pos < n && s[pos] != ')') right = parseNode(s, pos);
        while (pos < n && isspace((unsigned char)s[pos])) ++pos;
        if (pos < n && s[pos] == ')') ++pos; // consume ')'
        node->left = left;
        node->right = right;
    }
    return node;
}

bool isCompleteBinaryTree(TreeNode* root) {
    if (!root) return true;
    std::queue<TreeNode*> q;
    q.push(root);
    bool seenNull = false;
    while (!q.empty()) {
        TreeNode* cur = q.front(); q.pop();
        if (!cur) {
            seenNull = true;
        } else {
            if (seenNull) return false; // 在遇到空之后还有非空节点 => 不是完全二叉树
            q.push(cur->left);
            q.push(cur->right);
        }
    }
    return true;
}

// 释放内存
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    std::ifstream infile("in.txt");
    if (!infile) return 0;
    std::string line;
    // 读取第一行非空字符串作为一棵树
    std::string treeStr;
    while (std::getline(infile, line)) {
        // 去除行首尾空白
        bool allSpace = true;
        for (char c : line) if (!isspace((unsigned char)c)) { allSpace = false; break; }
        if (!allSpace) { treeStr = line; break; }
    }
    infile.close();
    if (treeStr.empty()) return 0;

    int pos = 0;
    TreeNode* root = parseNode(treeStr, pos);
    bool res = isCompleteBinaryTree(root);
    std::cout << (res ? "1" : "0") << std::endl;
    freeTree(root);
    return 0;
}