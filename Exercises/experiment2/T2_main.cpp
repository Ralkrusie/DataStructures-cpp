/*
2. 家谱
【问题描述】

     给定括号表示法的二叉树族谱，每个结点包含单个字符，表示一个人（每个结点字符是唯一的）。给定族谱中的两个人的字符，判断他们是否属于同一代，并分别输出这两个人的没有后代的子孙名字。

【输入形式】

     一共有两行，第一行为括号表示法的二叉树，第二行是用空格隔开的两个字符，为要判断是否为同一代的字符

【输出形式】

       一共两行，第一行: 如果是同一代输出True，如果不是同一代输出False

        第二行从左到右输出两个人没有后代的子孙节点, 不同字符的子孙节点用[ ]分隔, 没有满足要求的子孙节点就不用输出  

【样例1输入】

A(B(D,E(H)),C(F,G))

B C

【样例1输出】

True

[DH][FG]

【样例2输入】

A(B,C)

B C

【样例2输出】

True   

 【样例说明】

       测试样例1中 A，B，C......G均表示家族中的某个人，其中，B和C是同一代。D，E，F，G也是同一代，但是B和F就不是同一代。

       对于B，没有后代的子孙结点就是D和H，虽然E也是B的子孙结点，但是E有后代H，所以不能输出。对于C来说，没有后代的子孙结点就是F和G。

     测试样例2中，B，C是同一代，第一行输出True，B和C都没有子孙节点，所以第二行不需要输出

 【评分标准】

     一共5个测试用例，共50分，第一行全部通过得总分的60%，第二行全部通过得总分的40%。允许使用STL。
*/

#include <iostream>
#include <string>

struct TreeNode {
    char val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(char v) : val(v), left(nullptr), right(nullptr) {}
};

// 递归解析括号表示法的二叉树，pos 随解析推进
TreeNode *parseTree(const std::string &s, int &pos) {
    if (pos >= (int)s.size()) return nullptr;

    TreeNode *node = new TreeNode(s[pos]);
    ++pos;

    if (pos < (int)s.size() && s[pos] == '(') {
        ++pos; // 跳过 '('

        // 解析左孩子（可能为空）
        if (pos < (int)s.size() && s[pos] != ',' && s[pos] != ')') {
            node->left = parseTree(s, pos);
        }

        // 遇到逗号则解析右孩子
        if (pos < (int)s.size() && s[pos] == ',') {
            ++pos; // 跳过 ','
            if (pos < (int)s.size() && s[pos] != ')') {
                node->right = parseTree(s, pos);
            }
        }

        // 跳过 ')'
        if (pos < (int)s.size() && s[pos] == ')') {
            ++pos;
        }
    }

    return node;
}

// 在树中查找值为 target 的结点，并记录其深度（根深度为 0）
bool findDepth(TreeNode *root, char target, int depth, int &outDepth) {
    if (root == nullptr) return false;
    if (root->val == target) {
        outDepth = depth;
        return true;
    }
    return findDepth(root->left, target, depth + 1, outDepth) ||
           findDepth(root->right, target, depth + 1, outDepth);
}

// 在树中查找值为 target 的结点指针
TreeNode *findNode(TreeNode *root, char target) {
    if (root == nullptr) return nullptr;
    if (root->val == target) return root;
    TreeNode *found = findNode(root->left, target);
    if (found != nullptr) return found;
    return findNode(root->right, target);
}

// 先序遍历收集子树中的所有叶子结点（自身是叶子也会被收集）
void collectLeaves(TreeNode *node, std::string &result) {
    if (node == nullptr) return;
    if (node->left == nullptr && node->right == nullptr) {
        result.push_back(node->val);
        return;
    }
    collectLeaves(node->left, result);
    collectLeaves(node->right, result);
}

// 收集某人的"没有后代的子孙"：即从该结点出发，对其左右子树分别收集叶子
std::string leafDescendants(TreeNode *person) {
    if (person == nullptr) return "";
    std::string result;
    collectLeaves(person->left, result);
    collectLeaves(person->right, result);
    return result;
}

// 递归释放树内存
void deleteTree(TreeNode *root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    std::string treeStr;
    std::getline(std::cin, treeStr);

    char c1, c2;
    std::cin >> c1 >> c2;

    int pos = 0;
    TreeNode *root = parseTree(treeStr, pos);

    // 1. 判断是否同一代
    int depth1 = -1, depth2 = -1;
    findDepth(root, c1, 0, depth1);
    findDepth(root, c2, 0, depth2);

    if (depth1 == depth2)
        std::cout << "True" << std::endl;
    else
        std::cout << "False" << std::endl;

    // 2. 输出没有后代的子孙
    TreeNode *p1 = findNode(root, c1);
    TreeNode *p2 = findNode(root, c2);

    std::string leaves1 = leafDescendants(p1);
    std::string leaves2 = leafDescendants(p2);

    // 仅当至少一人有符合条件的子孙时才输出第二行
    if (!leaves1.empty() || !leaves2.empty()) {
        if (!leaves1.empty())
            std::cout << "[" << leaves1 << "]";
        if (!leaves2.empty())
            std::cout << "[" << leaves2 << "]";
        std::cout << std::endl;
    }

    deleteTree(root);
    return 0;
}
