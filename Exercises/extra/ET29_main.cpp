/*
4. 二叉树的序列化与反序列化
一、问题描述
实现二叉树的序列化和反序列化。序列化是将二叉树转换为字符串，反序列化是将字符串恢复为二叉树。

要求：

序列化：将二叉树按先序遍历序列化为字符串，空节点用#表示，节点值之间用逗号分隔

反序列化：将序列化字符串恢复为二叉树，然后输出其中序遍历序列验证正确性

二、输入形式


一行若干个整数，表示二叉树的先序遍历序列，空节点用-1表示。

三、输出形式
第一行输出序列化后的字符串。
第二行输出反序列化后二叉树的中序遍历序列。

四、样例输入

1 2 4 -1 -1 5 -1 -1 3 -1 -1
五、样例输出

1,2,4,#,#,5,#,#,3,#,#
4 2 5 1 3
六、样例说明
二叉树结构：

    1
   / \
  2   3
 / \
4   5
先序遍历：1,2,4,#,#,5,#,#,3,#,#
中序遍历：4 2 5 1 3

七、评分标准
共8个测试用例。

八、类库使用要求
必须手动实现二叉树结构，可以使用string、stringstream。
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../../Structures/et_tree_utils.hpp"

int main() {
    std::vector<int> values;
    int x;
    while (std::cin >> x) {
        values.push_back(x);
    }
    et::BinaryNode *root = et::buildPreorder(values);
    std::ostringstream oss;
    et::serialize(root, oss);
    std::string serialized = oss.str();
    std::cout << serialized << '\n';
    et::BinaryNode *restored = et::deserialize(serialized);
    bool first = true;
    et::inorder(restored, first);
    std::cout << '\n';
    et::destroy(root);
    et::destroy(restored);
    return 0;
}