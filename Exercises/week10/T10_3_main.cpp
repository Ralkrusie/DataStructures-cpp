/*
【问题描述】


给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值，这条路径可能穿过根结点也可能不穿过根结点。示例，给定一棵如图7.3所示的二叉树，返回3，它的长度是路径[4，2，1，3]或者[5，2，1，3]。



image.png

注意两结点之间的路径长度是以它们之间边的数目表示。假设给定的两棵二叉树可能会有1到200个结点，给定的二叉树树上的值介于0到200之间。二叉树采用二叉链存储，结点类型TreeNode如下：

struct TreeNode

{        intval;

          TreeNode *left;

          TreeNode *right;

          TreeNode(int x):val(x),left(NULL),right(NULL){}

};

设计如下成员函数：

class Solution {

public:

          int diameterOfBinaryTree(TreeNode *root)

          {  …  }

};


【输入形式】

       每个测试是一颗二叉树的括号表示法字符串
【输出形式】

       该二叉树的直径数值

【样例输入】

      1(2(4,5),3)

【样例输出】

      3
【样例说明】

     测试数据的文件名为in.txt
*/

#include <iostream>
#include <string>
#include <queue>
#include <cctype>
#include <fstream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// 递归解析：支持多位数与负数，允许空子树表示为"(,x)" 或 "(x,)"
TreeNode* parseNode(const std::string& s, int& pos) {
    int n = (int)s.size();
    while (pos < n && isspace((unsigned char)s[pos])) ++pos;
    if (pos >= n) return nullptr;
    if (s[pos] == ')' || s[pos] == ',') return nullptr; // 空子树

    // 解析整数
    int sign = 1;
    if (s[pos] == '+') { ++pos; }
    else if (s[pos] == '-') { sign = -1; ++pos; }
    if (pos >= n || !isdigit((unsigned char)s[pos])) return nullptr;
    long long val = 0;
    while (pos < n && isdigit((unsigned char)s[pos])) {
        val = val * 10 + (s[pos] - '0');
        ++pos;
    }
    TreeNode* node = new TreeNode((int)(val * sign));

    while (pos < n && isspace((unsigned char)s[pos])) ++pos;
    if (pos < n && s[pos] == '(') {
        ++pos; // consume '('
        // left child (可能为空)
        TreeNode* left = nullptr;
        if (pos < n && s[pos] != ',') left = parseNode(s, pos);
        while (pos < n && isspace((unsigned char)s[pos])) ++pos;
        if (pos < n && s[pos] == ',') ++pos; // consume ','
        // right child (可能为空)
        TreeNode* right = nullptr;
        if (pos < n && s[pos] != ')') right = parseNode(s, pos);
        while (pos < n && isspace((unsigned char)s[pos])) ++pos;
        if (pos < n && s[pos] == ')') ++pos; // consume ')'
        node->left = left;
        node->right = right;
    }
    return node;
}

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        depth(root, diameter);
        return diameter;
    }
private:
    int depth(TreeNode* node, int& diameter) {
        if (!node) return 0;
        int leftDepth = depth(node->left, diameter);
        int rightDepth = depth(node->right, diameter);
        diameter = std::max(diameter, leftDepth + rightDepth); // 更新直径
        return std::max(leftDepth, rightDepth) + 1; // 返回当前节点的深度
    }
};

int main() {
    std::ifstream infile("in.txt");
    std::string line;
    if (std::getline(infile, line)) {
        int pos = 0;
        TreeNode* root = parseNode(line, pos);
        Solution solution;
        int result = solution.diameterOfBinaryTree(root);
        std::cout << result << std::endl;
    }
    return 0;
}