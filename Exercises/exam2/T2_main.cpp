#include <iostream>
#include <string>
#include <map> //仅用于让结点值表示结点序号
#include <functional>
#include <algorithm>

using namespace std;

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
    int height = 0;
    explicit Node(int v): data(v) {}
};

int height(Node* node) {
    if (!node) {
        return 0;
    }
    node->height = 1 + max(height(node->left), height(node->right));
    return node->height;
}

int len(Node* node) {
    int lH = node->left ? node->left->height : 0;
    int rH = node->right ? node->right->height : 0;
    return lH + rH;
}

int f(Node* root) {
    int H = root->height;
    int result = 0;
    function<void(Node*)> g = [&](Node* current) {
        if (!current) {
            return;
        }
        if (len(current) > result) {
            result = len(current);
        }

        //2(h-1) > result 时才有可能更高.
        if (current->left) {
            if  (2 * current->left->height - 2 > result) {
                g(current->left);
            }
        }
        if (current->right) {
            if  (2 * current->right->height - 2 > result) {
                g(current->right);
            }
        }
    };
    g(root);
    return result;
}


int main() {
    int N;
    cin >> N;
    //cout << N;
    map<int, Node*> nodes;
    Node* root = nullptr;
    for (int i = 0; i < N; i++) {
        int num;

        // parent:
        cin >> num;
        //cout << num << ' ';
        if (nodes.find(num) == nodes.end()) {
            nodes.emplace(num, new Node(num));
            root = nodes[num];
        }
        Node* parent = nodes[num];

        // left:
        string str;
        cin >> str;
        //cout << str << ' ';
        if (str != "#") {
            num = stoi(str);
            if (nodes.find(num) == nodes.end()) {
                nodes.emplace(num, new Node(num));
            }
            parent->left = nodes[num];
        }

        // right:
        cin >> str;
        //cout << str << " - ";
        if (str != "#") {
            num = stoi(str);
            if (nodes.find(num) == nodes.end()) {
                nodes.emplace(num, new Node(num));
            }
            parent->right = nodes[num];
        }
    }

    if (!root) {
        cout << "0\n";
        return 0;
    }

    int rootHeight = height(root);
    cout << f(root) << endl;
}