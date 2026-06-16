/*
2. 二叉树镜像翻转
一、问题描述
给定一棵二叉树，将其镜像翻转（左右子树交换），然后输出翻转后的先序遍历序列。

二、输入形式
一行若干个整数，表示二叉树的先序遍历序列，空节点用-1表示。

三、输出形式
输出镜像翻转后的二叉树的先序遍历序列，空节点不输出。

四、样例输入



1 2 4 -1 -1 5 -1 -1 3 -1 6 -1 -1
五、样例输出

1 3 6 2 5 4
六、样例说明
原二叉树：

    1
   / \
  2   3
 / \   \
4   5   6
镜像翻转后：

    1
   / \
  3   2
 /   / \
6   5   4
先序遍历：1 3 6 2 5 4

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
    et::mirror(root);
    bool first = true;
    et::preorder(root, first);
    std::cout << '\n';
    et::destroy(root);
    return 0;
}