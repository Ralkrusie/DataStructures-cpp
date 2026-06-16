/*
8. 二叉树的创建与遍历
一、问题描述
根据给定的先序遍历序列创建二叉树（空节点用-1表示），然后输出中序、后序和层序遍历序列。

二、输入形式
一行若干个整数，表示二叉树的先序遍历序列，空节点用-1表示。

三、输出形式
输出三行，分别是中序、后序和层序遍历序列，节点值用空格分隔。

四、样例输入





1 2 4 -1 -1 5 -1 -1 3 -1 6 -1 -1
五、样例输出

4 2 5 1 3 6
4 5 2 6 3 1
1 2 3 4 5 6
六、样例说明
二叉树结构：

    1
   / \
  2   3
 / \   \
4   5   6
七、评分标准
共8个测试用例。

八、类库使用要求
必须手动实现二叉树结构和遍历算法，可以使用queue。


C
(current)

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
    bool first = true;
    et::inorder(root, first);
    std::cout << '\n';
    first = true;
    et::postorder(root, first);
    std::cout << '\n';
    et::levelorder(root);
    et::destroy(root);
    return 0;
}