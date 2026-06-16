/*
【问题描述】

实现一个平衡二叉树算法。接受一串待插入的字母序列插入到平衡二叉树中，再接受一串待删除的字母序列，输出删除之后二叉树的后序遍历。
【输入形式】

第一行，待插入字母个数N1；

第二行，间隔输入待插入的字母；

第三行，待删除字母个数N2；

第四行，间隔输入待删除的字母；

【输出形式】

第一行，输出后序遍历序列；
【样例输入】

6

a c g s e f

2

c s
【样例输出】

afge

【样例说明】
【评分标准】
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cstddef>
using namespace std;

struct AVLNode {
    char data;
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;
    int height;
    explicit AVLNode(char c) : data(c), height(1) {}
};

int getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

int getBalance(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void updateHeight(AVLNode* node) {
    if (node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

// 右旋
AVLNode* rightRotate(AVLNode* p) {
    AVLNode* l = p->left;
    AVLNode* lr = l->right;
    l->right = p;
    p->left = lr;
    updateHeight(p);
    updateHeight(l);
    return l;
}

// 左旋
AVLNode* leftRotate(AVLNode* p) {
    AVLNode* r = p->right;
    AVLNode* rl = r->left;
    r->left = p;
    p->right = rl;
    updateHeight(p);
    updateHeight(r);
    return(r);
}

// 插入节点
//node意思是current, key为插入的数值。
AVLNode* insert(AVLNode* node, char key) {
    if (!node) {
        AVLNode* newNode = new AVLNode(key);
        return newNode;
    }
    if (key < node->data) {
        node->left = insert(node->left, key);
    } else if (key > node->data) {
        node->right = insert(node->right, key);
    } else {
        return node;  // 重复键不插入
    }

    // 递归时沿着回来的路依次更新height:
    updateHeight(node);
    int balance = getBalance(node);

    // LL 型: balance > 1说明是L, key<左孩子，说明是LL;
    if (balance > 1 && key < node->left->data)
        //可能return到上一个node->left/right = 旋转后的父节点。
        return rightRotate(node);
    // RR 型
    if (balance < -1 && key > node->right->data)
        return leftRotate(node);
    // LR 型：左旋左孩子，再右旋
    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RL 型：右旋右孩子，再左旋
    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    //没有不平衡，直接返回
    return node;
}

// 找最小值节点
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left)
        current = current->left;
    return current;
}

// 删除节点
//node: current. key: 需要删除的结点的值
AVLNode* remove(AVLNode* node, char key) {
    if (!node) return node;

    if (key < node->data)
        node->left = remove(node->left, key);
    else if (key > node->data)
        node->right = remove(node->right, key);
    else { // key == node->data
        if (!node->left) {
            // 无左孩子，右孩子代替父节点，删除父节点
            AVLNode* right = node->right;
            delete node;
            return right;
        } else if (!node->right) {
            // 同理
            AVLNode* left = node->left;
            delete node;
            return left;
        } else {
            // 有两个子节点：用直接前驱/后继节点【替换】，这里用直接后继：右子树最小结点
            AVLNode* successor = minValueNode(node->right);
            // 【A替换B】：B的值改为A的值，删除A
            node->data = successor->data;
            node->right = remove(node->right, successor->data);
        }
    }

    // 以下平衡操作与插入同理。
    updateHeight(node);
    int balance = getBalance(node);

    // LL 型
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);
    // LR 型
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RR 型
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);
    // RL 型
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

// 后序遍历 左-右-父
void postOrder(AVLNode* node, string& result) {
    if (!node) return;
    postOrder(node->left, result);
    postOrder(node->right, result);
    result += node->data;
}




/*
第一行，待插入字母个数N1；

第二行，间隔输入待插入的字母；

第三行，待删除字母个数N2；

第四行，间隔输入待删除的字母；
*/
int main() {
    int n1, n2;
    char ch;

    cin >> n1;
    AVLNode* root = nullptr;
    for (int i = 0; i < n1; ++i) {
        cin >> ch;
        root = insert(root, ch);
    }

    cin >> n2;
    for (int i = 0; i < n2; ++i) {
        cin >> ch;
        root = remove(root, ch);
    }

    string result;
    postOrder(root, result);
    cout << result;

    return 0;
}

