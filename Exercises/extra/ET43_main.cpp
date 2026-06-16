/*
18. 第k小的元素
第k小的元素
一、问题描述
给定一棵二叉搜索树（BST），找出其中第k小的元素（1 ≤ k ≤ 节点总数）。

二、输入形式
第一行输入一个正整数k（1 ≤ k ≤ 10000）。
第二行输入若干个整数，表示BST的先序遍历序列，空节点用-1表示。

三、输出形式
输出一个整数，表示第k小的元素。

四、样例输入

3
5 3 2 -1 -1 4 -1 -1 6 -1 -1
五、样例输出

4
六、样例说明
BST结构：

    5
   / \
  3   6
 / \
2   4
中序遍历（升序）：2, 3, 4, 5, 6
第3小的元素是4。

七、评分标准
共8个测试用例。

八、类库使用要求
必须手动实现BST结构。
*/

#include <iostream>
#include <vector>

#include "../../Structures/et_tree_utils.hpp"

int main() {
    size_t k;
    std::cin >> k;
    std::vector<int> values;
    int x;
    while (std::cin >> x) {
        values.push_back(x);
    }
    et::BinaryNode *root = et::buildBSTFromPreorderSequence(values);
    size_t count = 0;
    int answer = -1;
    et::kthSmallest(root, k, count, answer);
    std::cout << answer << '\n';
    et::destroy(root);
    return 0;
}