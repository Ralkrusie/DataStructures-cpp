/*
8. 二叉树遍历
【问题描述】假设二叉树中每个结点值均为单个字符，采用链式的存储结构。分别输出该二叉树先序遍历中序遍历和后序遍历的结果。
【输入形式】

第一行：以括号表示法输入该二叉树的所有结点
【输出形式】

第一行：输出先序遍历的结果

第二行：输出中序遍历的结果

第三行：输出后序遍历的结果
【样例输入】

a(c,b)
【样例输出】

acb

cab

cba
【样例说明】

符号均为半角符号，中间无空格，输入字符串的长度不超过N（N<=100）
【提示】

如果不知道如何根据输入生成二叉链树，可看本提示(仅供参考，算法有多样，以下只有核心思路，具体请自行完善)。

可以先将输入存入到一维数组中，之后顺序扫描:

    若扫描到非括号且非逗号，存入当前结点，继续扫描；

    若扫描到左括号，继续：

        若扫描到非逗号非右括号，生成当前结点左子结点，递归扫描；

        若扫描到逗号，生成当前结点右子结点，递归扫描；

        若扫描到右括号，结束；

    若扫描到逗号或右括号，结束；
*/

#include <iostream>
#include <string>

class myBinaryTree {
public:
    myBinaryTree() : root(nullptr) {}

    ~myBinaryTree() {
        clearNode(root);
    }

    void buildFromBracket(const std::string &expr) {
        clearNode(root);
        size_t index = 0;
        root = parseNode(expr, index);
    }

    std::string preOrder() const {
        std::string out;
        preOrderNode(root, out);
        return out;
    }

    std::string inOrder() const {
        std::string out;
        inOrderNode(root, out);
        return out;
    }

    std::string postOrder() const {
        std::string out;
        postOrderNode(root, out);
        return out;
    }

private:
    struct Node {
        char value;
        Node *left;
        Node *right;
        explicit Node(char x) : value(x), left(nullptr), right(nullptr) {}
    };

    static Node *parseNode(const std::string &s, size_t &i) {
        if (i >= s.size()) {
            return nullptr;
        }
        if (s[i] == '(' || s[i] == ')' || s[i] == ',') {
            return nullptr;
        }

        Node *node = new Node(s[i]);
        ++i;

        if (i < s.size() && s[i] == '(') {
            ++i;
            if (i < s.size() && s[i] != ',' && s[i] != ')') {
                node->left = parseNode(s, i);
            }
            if (i < s.size() && s[i] == ',') {
                ++i;
                if (i < s.size() && s[i] != ')') {
                    node->right = parseNode(s, i);
                }
            }
            if (i < s.size() && s[i] == ')') {
                ++i;
            }
        }
        return node;
    }

    static void preOrderNode(Node *current, std::string &out) {
        if (current == nullptr) {
            return;
        }
        out.push_back(current->value);
        preOrderNode(current->left, out);
        preOrderNode(current->right, out);
    }

    static void inOrderNode(Node *current, std::string &out) {
        if (current == nullptr) {
            return;
        }
        inOrderNode(current->left, out);
        out.push_back(current->value);
        inOrderNode(current->right, out);
    }

    static void postOrderNode(Node *current, std::string &out) {
        if (current == nullptr) {
            return;
        }
        postOrderNode(current->left, out);
        postOrderNode(current->right, out);
        out.push_back(current->value);
    }

    static void clearNode(Node *current) {
        if (current == nullptr) {
            return;
        }
        clearNode(current->left);
        clearNode(current->right);
        delete current;
    }

    Node *root;
};

int main() {
    std::string expr;
    std::getline(std::cin, expr);
    while (expr.empty() && std::cin.good()) {
        std::getline(std::cin, expr);
    }

    myBinaryTree tree;
    tree.buildFromBracket(expr);

    std::cout << tree.preOrder() << '\n';
    std::cout << tree.inOrder() << '\n';
    std::cout << tree.postOrder() << '\n';
    return 0;
}