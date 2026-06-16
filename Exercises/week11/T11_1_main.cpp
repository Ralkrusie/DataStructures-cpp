/*
哈夫曼树与哈夫曼编码
一、问题描述
给定n个字符及其出现频率，构建哈夫曼树并计算WPL（带权路径长度）。

WPL定义：所有叶子节点的带权路径长度之和，其中带权路径长度 = 权值 × 路径长度（从根到叶子的边数）。

二、输入形式
第一行输入一个正整数n（1 ≤ n ≤ 10000），表示字符数量。
第二行输入n个正整数，表示各字符的出现频率（权值）。

三、输出形式
输出一个整数，表示WPL值。

四、样例输入

4
5 29 7 8
五、样例输出

81
六、样例说明
频率：A=5, B=29, C=7, D=8

哈夫曼树构建过程：

排序：5, 7, 8, 29

合并5+7=12，排序：8, 12, 29

合并8+12=20，排序：20, 29

合并20+29=49

WPL = 5×3 + 7×3 + 8×2 + 29×1 = 15 + 21 + 16 + 29 = 81

（注：不同合并顺序可能产生不同树形，但WPL相同）

七、评分标准
共10个测试用例。

八、类库使用要求
可以使用priority_queue（小顶堆），禁止使用其他容器。
*/

#include <iostream>
#include <queue>
#include <stack>

struct HTNode {
    int value;
    HTNode* leftNode = nullptr;
    HTNode* rightNode = nullptr;
    HTNode* parent = nullptr;
    bool isLeft = false;
    HTNode(int v): value(v) {}
};

struct HeapNode {
    HTNode* node;

    HeapNode(const int& v):  node(new HTNode(v)) {}
    HeapNode(HTNode* n): node(n) {}

    bool operator<(const HeapNode& other) const {
        return this->node->value > other.node->value;
    }
};

// 计算WPL的方法一，不好，容易爆栈。
// int badlyCalculateWPLRecursive(HTNode* root, int level) {
//     if (root == nullptr) {
//         return 0;
//     }

//     if (!root->leftNode && !root->rightNode) {
//         return level * root->value;
//     }

//     return calculateWPL(root->leftNode, level + 1) + calculateWPL(root->rightNode, level + 1);
// }

// 计算WPL的方法二，较好。
// long long calculateWPLIterative(HTNode* root) {
//     if (root == nullptr) {
//         return 0;
//     }

//     struct StackItem {
//         HTNode* node;
//         int level;
//     };

//     std::stack<StackItem> stack;
//     stack.push({ root, 0 });

//     long long result = 0;

//     while (!stack.empty()) {
//         StackItem current = stack.top();
//         stack.pop();

//         if (current.node->leftNode == nullptr && current.node->rightNode == nullptr) {
//             result += static_cast<long long>(current.level) * current.node->value;
//             continue;
//         }

//         if (current.node->rightNode != nullptr) {
//             stack.push({ current.node->rightNode, current.level + 1 });
//         }

//         if (current.node->leftNode != nullptr) {
//             stack.push({ current.node->leftNode, current.level + 1 });
//         }
//     }

//     return result;
// }



int main() {
    int n;
    std::cin >> n;
    std::priority_queue<HeapNode> heap;
    HTNode* HTRoot = nullptr;
    for (int i = 0; i < n; i++) {
        int v;
        std::cin >> v;
        heap.push(HeapNode(v));
    }

    int result = 0;

    while (!heap.empty()) {
        HeapNode a = heap.top();
        heap.pop();
        if (heap.empty()) {
            HTRoot = a.node;
            break;
        }
        HeapNode b = heap.top();
        heap.pop();

        a.node->isLeft = true;
        b.node->isLeft = false;

        int parentValue = a.node->value + b.node->value;
        HTNode* newParent = new HTNode(parentValue);
        result += parentValue;

        newParent->leftNode = a.node;
        newParent->rightNode = b.node;
        a.node->parent = newParent;
        b.node->parent = newParent;

        HTRoot = newParent;

        if (!heap.empty()) {
            heap.push(HeapNode(newParent));
        }
    }

    std::cout << result <<std::endl;

    return 0;
}



