/*
【问题描述】

在给定的二叉树结构中，每个结点值为单个字符。设计一个算法，采用先序遍历方法求出某个值为x的结点的所有子孙。



【输入形式】

输入由多行组成：

第一行为一个整数N，表示二叉树中结点的数量。

接下来N行，每行描述一个结点的信息，格式为：父节点值 左孩子值 右孩子值

如果某个孩子为空，则用‘#’表示。

最后一行为目标字符x。

【输出形式】

按先序遍历的顺序输出包含所有目标节点x的子孙结点值。



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
#include <unordered_map>
#include <string>

int main() {
    int N;
    std::cin >> N;

    std::unordered_map<char, std::pair<char, char>> tree;
    char parent, left, right;

    for (int i = 0; i < N; ++i) {
        std::cin >> parent >> left >> right;
        tree[parent] = {left, right};
    }

    char target;
    std::cin >> target;

    std::vector<char> descendants;
    std::vector<char> stack = {target};

    while (!stack.empty()) {
        char current = stack.back();
        stack.pop_back();

        if (current != '#' && tree.find(current) != tree.end()) {
            descendants.push_back(current);
            stack.push_back(tree[current].second); // right child
            stack.push_back(tree[current].first);  // left child
        }
    }

    for (size_t i = 1; i < descendants.size(); ++i) { // Skip the target node itself
        std::cout << descendants[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}