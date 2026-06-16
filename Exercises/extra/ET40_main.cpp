/*
15. BST转有序双向链表
BST转有序双向链表
一、问题描述
给定一棵二叉搜索树（BST），将其转换为一个有序双向链表。要求不能创建新节点，只能调整指针指向。

双向链表要求：

节点值按升序排列

每个节点有prev和next指针

输出链表的头节点和尾节点值

二、输入形式
一行若干个整数，表示BST的先序遍历序列，空节点用-1表示。

三、输出形式
输出一行两个整数，分别表示双向链表的头节点和尾节点值。

四、样例输入

4 2 1 -1 -1 3 -1 -1 5 -1 -1
五、样例输出

1 5
六、样例说明
BST结构：

    4
   / \
  2   5
 / \
1   3
中序遍历：1 2 3 4 5
转换为双向链表：1 ↔ 2 ↔ 3 ↔ 4 ↔ 5
头节点是1，尾节点是5。

七、评分标准
共10个测试用例。

八、类库使用要求
必须手动实现二叉树结构。
*/

#include <iostream>
#include <vector>

#include "../../Structures/et_tree_utils.hpp"

static void linkInorder(et::BinaryNode *node, et::BinaryNode *&head, et::BinaryNode *&previous) {
    if (node == nullptr) {
        return;
    }
    linkInorder(node->left, head, previous);
    if (previous == nullptr) {
        head = node;
    } else {
        previous->right = node;
        node->left = previous;
    }
    previous = node;
    linkInorder(node->right, head, previous);
}

int main() {
    std::vector<int> values;
    int x;
    while (std::cin >> x) {
        values.push_back(x);
    }
    et::BinaryNode *root = et::buildBSTFromPreorderSequence(values);
    et::BinaryNode *head = nullptr;
    et::BinaryNode *previous = nullptr;
    linkInorder(root, head, previous);
    if (head == nullptr) {
        std::cout << "EMPTY\n";
    } else {
        std::cout << head->value << ' ' << previous->value << '\n';
    }

    et::BinaryNode *current = head;
    while (current != nullptr) {
        et::BinaryNode *next = current->right;
        current->left = nullptr;
        current->right = nullptr;
        delete current;
        current = next;
    }
    return 0;
}