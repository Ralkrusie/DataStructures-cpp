#include <iostream>
#include <sstream>
#include <string>
#include <stack>
using namespace std;

struct Node {
    char data;
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(int v): data(v) {}
};

Node* build(const string& str, int& p) {
    if (p >= str.size()) {
        return nullptr;
    }
    char ch = str[p];
    if (ch == ',' || ch == ')') {
        return nullptr;
    }

    Node* newNode = new Node(ch);
    p++;
    char nextCh = str[p];
    if (nextCh == '(') {
        //left:
        p++;
        if (str[p] == ',') {
            p++;
            newNode->left = nullptr;
        } else if (str[p] == ')') {
            newNode->left = nullptr;
        } else {
            newNode->left = build(str, p);
            p++;
        }

        //right:
        if (str[p] == ',') {
            p++;
        }
        if (str[p] == ')') {
            newNode->right = nullptr;
            p++;
        } else {
            newNode->right = build(str, p);
        }
    }
    return newNode;
}

void postOrder(Node* node) {
    if (node->left) {
        postOrder(node->left);
    }
    if (node->right) {
        postOrder(node->right);
    }
    cout << node->data;
}


int main() {
    string line;
    getline(cin, line);
    int pos = 0;
    Node* root = build(line, pos);
    if (root) {
        postOrder(root);
        return 0;
    }
    cout << '\0';
    return 0;
}