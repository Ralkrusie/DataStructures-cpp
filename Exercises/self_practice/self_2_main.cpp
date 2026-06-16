#include <iostream>
#include <string>
#include <map>
#include <functional>

using namespace std;

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(int v): data(v) {}
};

int maxFlow(Node* root) {
    int result = 0;
    function<void(Node*,int)> f = [&](Node* current, int path) {
        if (!current) {
            if (path > result) {
                result = path;
            }
            return;
        }

        if (path == -1 || (path >= 0 && path > current->data)) {
            path = current->data;
        }
        
        f(current->left, path);
        f(current->right, path);
    };

    f(root, -1);
    return result;
}

int main() {
    int N;
    cin >> N;
    map<int, Node*> nodes;
    Node* root = nullptr;
    for (int i = 0; i < N; i++) {
        int num;

        // parent:
        cin >> num;
        // C++20：nodes.contains(num)
        if (nodes.find(num) == nodes.end()) {
            nodes.emplace(num, new Node(num));
            root = nodes[num];
        }
        Node* parent = nodes[num];

        // left:
        string str;
        cin >> str;
        if (str != "#") {
            num = stoi(str);
            if (nodes.find(num) == nodes.end()) {
                nodes.emplace(num, new Node(num));
            }
            parent->left = nodes[num];
        }

        // right:
        cin >> str;
        if (str != "#") {
            num = stoi(str);
            if (nodes.find(num) == nodes.end()) {
                nodes.emplace(num, new Node(num));
            }
            parent->right = nodes[num];
        }
    }

    cout << maxFlow(root) << endl;
}