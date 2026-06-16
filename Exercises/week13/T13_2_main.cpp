/*
2. 第九章第16题
【问题描述】

给定一个整数二叉排序树（BST），设计一个算法，查找值大于 k 的值最小的结点。如果存在这样的结点，返回该结点的值；否则，返回 -1。

二叉排序树的性质：

左子树的所有结点的值均小于根结点的值。

右子树的所有结点的值均大于根结点的值。

左右子树也分别是二叉排序树。


【输入形式】

第一行输入一个整数 n，表示二叉排序树的结点数量。

第二行输入 n 个整数，表示二叉排序树的结点值，按层序遍历顺序给出（空结点用 -1 表示）。

第三行输入一个整数 k，表示要查找的目标值。



【输出形式】

输出一个整数，表示二叉排序树中值大于 k 的值最小的结点的值。如果不存在这样的结点，输出 -1。



【样例输入】

7

4 2 6 1 3 5 7

3
【样例输出】

4


【样例说明】

输入的二叉排序树结构如下：

    4
   / \
  2   6
 / \ / \
1  3 5  7
查找值大于 3 的值最小的结点，因此输出 4。
*/

#include <iostream>
#include <queue>
#include <functional>
using namespace std;


struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(int v): data(v) {}
};

int successor(Node* root, int target) {
    priority_queue<int, vector<int>, greater<int>> heap;
    function<void(Node*)> f = [&](Node* current) {
        if (current->data > target) {
            heap.push(current->data);
            if (current->left) {
                f(current->left);
            }
        } else {
            if (current->right) {
                f(current->right);
            }
        }
    };
    f(root);
    if (heap.empty()) {
        return -1;
    }
    return heap.top();
}

int main() {
    int n;
    cin >> n;

    //cout << "输入：\n" << n << endl;

    int value;
    Node* root = new Node(-1);
    queue<Node**> qu;
    qu.push(&root);
    while (!qu.empty()) {
        if (n == 0) {
            Node** current = qu.front();
            qu.pop();
            delete *current;
            *current = nullptr;
            continue;
        }
        cin >> value;

        //cout << value << ' ';

        Node** current = qu.front();
        qu.pop();
        if (value == -1) {
            delete *current;
            *current = nullptr;
        } else {
            (*current)->data = value;
            n--;
            if (n > 0) {
                (*current)->left = new Node(-1);
                qu.push(&(*current)->left);
            }
            if (n > 0) {
                (*current)->right = new Node(-1);
                qu.push(&(*current)->right);
            }
        }
    }
    int target;
    cin >> target;

    //cout << '\n' << target << endl; 

    cout << successor(root, target) << endl;
}