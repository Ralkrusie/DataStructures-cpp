/*
1. 判断二叉树是否对称
一、问题描述
给定一棵二叉树，检查它是否是轴对称的（镜像对称）。

二、输入形式
一行若干个整数，表示二叉树的先序遍历序列，空节点用-1表示。

三、输出形式
输出"YES"表示对称，输出"NO"表示不对称。

四、样例输入

1 2 3 -1 -1 4 -1 -1 2 4 -1 -1 3 -1 -1
五、样例输出

YES
六、样例说明
对称二叉树：

    1
   / \
  2   2
 / \ / \
3  4 4  3
以根节点为轴，左右子树镜像对称。

七、评分标准
共8个测试用例。

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
    std::cout << (et::isSymmetric(root) ? "YES" : "NO") << '\n';
    et::destroy(root);
    return 0;
}