/*
1. 第七章 先序遍历输出二叉树 bt 中所有结点的层次
【问题描述】假设二叉树中的每个结点值为单个字符，采用二叉链存储结构存储。请设计一个算法，采用先序遍历的方法输出二叉树 bt 中所有结点的层次（根结点所在层为 1）。

【输入形式】
第一行输入一个整数 n，表示二叉树的结点数（1 ≤ n ≤ 1000）。

接下来 n 行，每行输入一个结点的信息，格式为：

结点值 左子结点值 右子结点值

【输出形式】

按先序遍历顺序依次输出结点的值及其所在的层次，每个结点占一行，格式如下：

结点值 层次

【样例输入】

7

A B C

B D E

C # F

D # #

E # #

F G #

G # #

【样例输出】

A 1

B 2

D 3

E 3

C 2

F 3

G 4

【样例说明】
【评分标准】

【说明】

需要用二叉链存储结构实现


*/
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <string>
using namespace std;

struct TreeNode {
    char val;
    TreeNode *left, *right;
    TreeNode(char v) : val(v), left(nullptr), right(nullptr) {}
};

int main() {
    int n;
    cin >> n;
    if (n == 0) return 0;
    
    vector<TreeNode*> nodes(n + 1, nullptr);
    vector<char> leftVal(n + 1, '#'), rightVal(n + 1, '#');
    
    unordered_map<char, vector<int>> valueToIndices;
    

    for (int i = 1; i <= n; ++i) {
        char v, l, r;
        cin >> v >> l >> r;
        nodes[i] = new TreeNode(v);
        leftVal[i] = l;
        rightVal[i] = r;
        valueToIndices[v].push_back(i);
    }
    
    vector<bool> usedAsChild(n + 1, false);
    auto findChildIndex = [&](char val) -> int {
        if (val == '#') return -1;
        auto it = valueToIndices.find(val);
        if (it == valueToIndices.end()) return -1;
        for (int idx : it->second) {
            if (!usedAsChild[idx]) return idx;
        }
        return -1;
    };
    
    for (int i = 1; i <= n; ++i) {
        int leftIdx = findChildIndex(leftVal[i]);
        if (leftIdx != -1) {
            nodes[i]->left = nodes[leftIdx];
            usedAsChild[leftIdx] = true;
        }
        int rightIdx = findChildIndex(rightVal[i]);
        if (rightIdx != -1) {
            nodes[i]->right = nodes[rightIdx];
            usedAsChild[rightIdx] = true;
        }
    }
    
    TreeNode* root = nullptr;
    for (int i = 1; i <= n; ++i) {
        if (!usedAsChild[i]) {
            root = nodes[i];
            break;
        }
    }
    
    if (root) {
        stack<pair<TreeNode*, int>> st;
        st.push({root, 1});
        while (!st.empty()) {
            auto [node, level] = st.top();
            st.pop();
            cout << node->val << " " << level << endl;
            if (node->right) st.push({node->right, level + 1});
            if (node->left)  st.push({node->left, level + 1});
        }
    }

    for (int i = 1; i <= n; ++i) delete nodes[i];
    
    return 0;
}