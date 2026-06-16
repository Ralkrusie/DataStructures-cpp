/*
2. 第七章 求值为X的结点所在的最小层次
【问题描述】假设二叉树中的每个结点值为单个字符，采用二叉链存储结构存储。二叉树bt可能有多个值为x的结点，每个这样的结点对应一个层次（根结点为第1层）。请设计一个算法，求值为 x 的结点所在的最小层次。

【输入形式】

第一行输入一个整数 n，表示二叉树的结点数（1 ≤ n ≤ 1000）。

接下来 n 行，每行输入一个结点的信息，格式为：

结点值 左子结点值 右子结点值

若左子结点或右子结点为空，则用字符 # 表示。

最后一行输入一个字符 x，表示要查找的目标结点值。

【输出形式】

输出一个整数，表示所有值为 x 的结点中，所处的最小层次。

若不存在则输出-1

【样例输入】

7

A B C

B D E

C # F

D # #

E # #

F G #

G # #

E

【样例输出】

3
【样例说明】
【评分标准】

【说明】

需要用二叉链存储结构实现


*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

struct TreeNode {
    char val;
    TreeNode *left, *right;
    TreeNode(char v) : val(v), left(nullptr), right(nullptr) {}
};

int main() {
    int n;
    cin >> n;
    if (n == 0) {
        char x;
        cin >> x;
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

    TreeNode* root = nullptr;
    for (int i = 1; i <= n; ++i) {
        if (!usedAsChild[i]) {
            root = nodes[i];
            break;
        }
    }

    char x;
    cin >> x;

    if (root == nullptr) {
        cout << -1 << endl;
    } else {
        queue<pair<TreeNode*, int>> q;
        q.push({root, 1});
        bool found = false;
        while (!q.empty()) {
            auto [node, level] = q.front();
            q.pop();
            if (node->val == x) {
                cout << level << endl;
                found = true;
                break;
            }
            if (node->left)  q.push({node->left, level + 1});
            if (node->right) q.push({node->right, level + 1});
        }
        if (!found) cout << -1 << endl;
    }

    for (int i = 1; i <= n; ++i) delete nodes[i];

    return 0;
}