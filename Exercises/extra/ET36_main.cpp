/*
11. 二叉搜索树的最近公共祖先
二叉搜索树的最近公共祖先
一、问题描述
给定一棵二叉搜索树（BST）和两个节点p、q，找到它们的最近公共祖先（LCA）。

利用BST的性质：左子树所有节点值 < 根节点值 < 右子树所有节点值。

二、输入形式
第一行输入两个整数p和q。
第二行输入若干个整数，表示BST的先序遍历序列，空节点用-1表示。

三、输出形式
输出一个整数，表示p和q的最近公共祖先的节点值。

四、样例输入

2 8
6 2 0 -1 -1 4 -1 -1 8 -1 -1
五、样例输出

6
六、样例说明
BST结构：

    6
   / \
  2   8
 / \
0   4
节点2和节点8的LCA是6。

利用BST性质：

如果p和q分别在根的两侧，则根就是LCA

如果p和q都在左子树，递归在左子树查找

如果p和q都在右子树，递归在右子树查找

七、评分标准
共8个测试用例。

八、类库使用要求
必须手动实现BST结构。
*/

#include <iostream>
#include <vector>

#include "../../Structures/et_tree_utils.hpp"

int main() {
    int p, q;
    std::cin >> p >> q;
    std::vector<int> values;
    int x;
    while (std::cin >> x) {
        values.push_back(x);
    }
    et::BinaryNode *root = et::buildBSTFromPreorderSequence(values);
    if (!et::containsBST(root, p) || !et::containsBST(root, q)) {
        std::cout << -1 << '\n';
    } else {
        et::BinaryNode *ancestor = et::bstLca(root, p, q);
        std::cout << (ancestor == nullptr ? -1 : ancestor->value) << '\n';
    }
    et::destroy(root);
    return 0;
}