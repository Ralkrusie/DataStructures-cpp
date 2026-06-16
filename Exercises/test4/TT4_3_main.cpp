/*
3. 第七章 先序遍历方法求出某个值的所有子孙

【问题描述】

在给定的二叉树结构中，每个结点值为单个字符。设计一个算法，采用先序遍历方法求出某个值为x的结点的所有子孙。需先构建二叉链。



【输入形式】

输入由多行组成：

第一行为一个整数N，表示二叉树中结点的数量。

接下来N行，每行描述一个结点的信息，格式为：父节点值 左孩子值 右孩子值

如果某个孩子为空，则用‘#’表示。

最后一行为目标字符x。

【输出形式】

按先序遍历的顺序输出所有目标节点x的子孙结点值。



【样例输入】

6

A B C

B D E

C # F

D # #

E # #

F # #

B



【样例输出】

D E
*/
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

struct TreeNode {
    char val;
    TreeNode *left, *right;
    TreeNode(char v) : val(v), left(nullptr), right(nullptr) {}
};

void preorderPrint(TreeNode* root) {
    if (!root) return;
    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();
        cout << node->val << " ";
        if (node->right) st.push(node->right);
        if (node->left)  st.push(node->left);
    }
}

int main() {
    int n;
    cin >> n;
    if (n == 0) {
        char x; cin >> x;
        cout << -1 << endl;
        return 0;
    }

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

    char x;
    cin >> x;

    TreeNode* target = nullptr;
    for (int i = 1; i <= n; ++i) {
        if (nodes[i]->val == x) {
            target = nodes[i];
            break;
        }
    }

    if (target == nullptr) {
        cout << -1;
    } else {
        preorderPrint(target->left);
        preorderPrint(target->right);
    }
    cout << endl;

    for (int i = 1; i <= n; ++i) delete nodes[i];

    return 0;
}
