/*
6. 求二叉树叶子节点数
一、问题描述
给定一棵二叉树，计算树中叶子节点（度为0的节点）的数量。

二、输入形式
一行若干个整数，表示二叉树的先序遍历序列，空节点用-1表示。

三、输出形式
输出一个整数，表示二叉树的叶子节点数。

四、样例输入



1 2 4 -1 -1 5 -1 -1 3 -1 6 -1 -1
五、样例输出

3
六、样例说明
二叉树结构：

    1
   / \
  2   3
 / \   \
4   5   6
叶子节点为4、5、6，共3个。

七、评分标准
共10个测试用例。

八、类库使用要求
必须手动实现二叉树结构。
*/

#include <iostream>
#include <vector>

#include "../../Structures/et_tree_utils.hpp"

int main() {
    std::vector<int> values;
    int x;
    while (std::cin >> x) {
        values.push_back(x);
    }
    et::BinaryNode *root = et::buildPreorder(values);
    std::cout << et::countLeaves(root) << '\n';
    et::destroy(root);
    return 0;
}