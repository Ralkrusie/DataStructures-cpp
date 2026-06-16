/*
7. 园区外围安保巡逻
问题描述
某园区道路呈二叉树状。保安需沿最外围道路逆时针巡逻一圈：

从主入口（根）出发，沿左侧外围一直向下到最左叶子（记录沿途节点）

收集所有底层叶子节点（从左到右，不含已记录的两个端点）

沿右侧外围从右下叶子返回根（记录沿途节点，逆序）

任务
输出逆时针外围巡逻经过的景点编号序列，空格分隔。

输入形式
输入由多行组成：

第一行为一个整数 N，表示二叉树中结点的数量。

接下来 N 行，每行描述一个结点的信息，格式为：

父节点值 左孩子值 右孩子值
如果某个孩子为空，则用 # 表示。

第一行即为根节点，格式同样为 父节点值 左孩子值 右孩子值，其中「父节点值」就是根节点自身的值。

节点值为非负的整数，整数不大于109。

输出形式
一行整数，空格分隔，表示逆时针外围巡逻路线上的景点编号。

样例输入
6
1 2 3
2 4 5
3 # #
4 # #
5 # 6
6 # #
样例输出
1 2 4 6 3
样例说明
树结构如下：

    1
   / \
  2   3
 / \
4   5
     \
      6
左边界（从根到最左叶子）：1 → 2 → 4

去掉已在叶子中记录的最左端点 4

左边界输出：1 2

所有叶子（从左到右）：4 6 3

最左叶子 4 已在左边界端点

最右叶子 3 将在右边界端点

中间叶子：6

右边界（从最右叶子到根）：3 → 1

去掉根 1（已在左边界）和最右叶子 3（已在叶子中）

右边界输出：空

巡逻路线：1 2 4 6 3

注意：节点 5 不是叶子（它有右孩子 6），所以不单独出现在巡逻路线中。

评分标准
本题目共 10 个测试用例。

类库使用要求
禁止使用 STL 中的树形结构库（如 std::map 嵌套模拟树）

仅允许使用标准输入输出库（如 iostream、cstdio 等）

允许使用vector、stack、queue容器库。

需自行实现二叉树的节点结构与遍历逻辑

未按题意进行编码求解，扣减得分的50%
*/
#include <iostream>
#include <map>
#include <string>
#include <deque>
#include <functional>

using namespace std;

struct Node {
    string data;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    Node(const string& v) : data(v) {}
    Node(const string& v, Node* const p) : data(v), parent(p) {}
};

bool isLeaf(const Node* node) {
    return !(node->left || node->right);
}

void path(Node* root) {
    deque<Node*> path;
    // 从左到右的叶子
    function<void(Node*)> buildLeaves = [&](Node* node) {
        if (node->left) {
            buildLeaves(node->left);
        }
        if (isLeaf(node)) {
            path.push_back(node);
        }
        if (node->right) {
            buildLeaves(node->right);
        }
    };
    // 从上到下的左路
    function<void(Node*)> buildLeftEdge = [&](Node* node) {
        if (node->parent) {
            path.push_front(node->parent);
            buildLeftEdge(node->parent);
        }
    };
    // 从下到上的右路（去除根节点）
    function<void(Node*)> buildRightEdge = [&](Node* node) {
        if (node->parent) {
            if (node->parent->parent) {
                path.push_back(node->parent);
                buildRightEdge(node->parent);
            }
        }
    };
    
    buildLeaves(root);
    buildLeftEdge(path.front());
    buildRightEdge(path.back());
    
    for (const auto& node : path) {
        cout << node->data << ' ';
    }
}

int main() {
    int n;
    cin >> n;
    Node* root = nullptr;
    map<string, Node*> temp;
    for (int i = 0; i < n; i++) {
        string p;
        cin >> p;
        if (temp.find(p) == temp.end()) {
            temp.emplace(p, new Node(p));
            root = temp[p];
        }
        Node* parent = temp[p];

        // left
        string l;
        cin >> l;
        if (l != "#") {
            if (temp.find(l) == temp.end()) {
                temp.emplace(l, new Node(l, parent));
            }
            parent->left = temp[l];
        }

        // right
        string r;
        cin >> r;
        if (r != "#") {
            if (temp.find(r) == temp.end()) {
                temp.emplace(r, new Node(r, parent));
            }
            parent->right = temp[r];
        }
    }
    path(root);
}