/*
【问题描述】

常见的算术表达式是中缀表达式，运算符在两个操作数中间，例如，(x+y)*(z-w)就是一个中缀表达式。后缀表达式（也称为逆波兰表达式）将运算符写在两个操作数的后面，例如，x y + z w-*是后缀表达式，其中仅仅给出运算符和操作数，不包含括号。计算后缀表达式值需要使用栈，栈是一种支持两种操作的数据结构：push用于在栈顶插入一个数字，pop用于从栈顶部取出一个数字。

    在求值过程中从左到右处理表达式，如果遇到数字，则将其进栈；如果遇到运算符，则从栈中弹出前两个数字，将运算符应用于它们，然后将结果进栈。以下伪代码表示遇到运算符O时的处理方式：

      a := pop();

      b := pop();

      push(b O a);

    最后栈中唯一数字就是表达式值。现在想象一下，我们使用队列而不是栈计算表达式值。队列也有进队和出队运算，但它们的含义不同：push用于在队尾插入一个数字，pop用于将队头数字取出并删除。

【输入形式】

    每个样例是一行，包含一个后缀表达式，其中运算符用大写字母表示，数字用小写字母表示。你可以假定每个表达式的长度小于10000个字符。

【输出形式】

   每个输出是一行，对于每个给定的表达式，有一个采用栈求表达式值的顺序串，现在要求采用队列实现，并且输出这个相同的求表达式值的顺序串。

【样例输入】

   xyPzwIM

【样例输出】

   wzyxIPM

【样例说明】

     测试数据的文件名为in.txt
*/
#include <iostream>
#include <fstream>
#include <cctype>
#include <stack>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>

struct TreeNode {
    char value;
    TreeNode* leftChild = nullptr;
    TreeNode* rightChild = nullptr;
    bool isOperator = false;
    TreeNode(char v,bool op): value(v), isOperator(op) {}
};

std::vector<std::vector<char>>  reLevel(TreeNode* root) {
    std::vector<std::vector<char>> result;
    if (!root) {
        return result;
    }
    std::queue<TreeNode*> qu;
    qu.push(root);

    while (!qu.empty()) {
        int currentLevelSize = qu.size();
        std::vector<char> currentLevel;
        for (int i = 0; i < currentLevelSize; i++) {
            TreeNode* node = qu.front();
            qu.pop();
            currentLevel.push_back(node->value);
            if (node->leftChild) {
                qu.push(node->leftChild);
            }
            if (node->rightChild) {
                qu.push(node->rightChild);
            }
        }
        result.push_back(currentLevel);
    }
    std::reverse(result.begin(), result.end());
    return result;
}


int main() {
    std::ifstream fin;
    fin.open("in.txt");
    std::string input;
    fin >> input;
    //std::cin >> input;
    std::stack<TreeNode*> st;
    TreeNode* root = nullptr;
    for (char ch : input) {
        if (std::isupper(ch)) {
            TreeNode* op = new TreeNode(ch, true);
            op->leftChild = st.top();
            st.pop();
            op->rightChild = st.top();
            st.pop();
            st.push(op);
            root = op;
        } else {
            st.push(new TreeNode(ch, false));
        }
    }
    for (const auto& level : reLevel(root)) {
        for (char ch : level) {
            std::cout << ch;
        }
    }
}