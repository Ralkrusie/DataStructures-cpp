#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 定义二叉树节点结构
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    vector<int> res; // 存储最终结果

    // 1. 添加左边界（不包括边界上的叶子结点）
    void addLeftBoundary(TreeNode* root) {
        if (!root || (!root->left && !root->right)) return; // 遇到空节点或叶子节点停止
        
        res.push_back(root->val);
        
        // 优先向左走，如果没有左孩子则向右走
        if (root->left) {
            addLeftBoundary(root->left);
        } else {
            addLeftBoundary(root->right);
        }
    }

    // 2. 添加所有叶子节点（从左到右）
    void addLeaves(TreeNode* root) {
        if (!root) return;
        
        // 如果是叶子节点，加入结果
        if (!root->left && !root->right) {
            res.push_back(root->val);
            return;
        }
        
        addLeaves(root->left);
        addLeaves(root->right);
    }

    // 3. 添加右边界（注意是逆时针，所以应该是从底部往上的顺序加入结点）
    void addRightBoundary(TreeNode* root) {
        if (!root || (!root->left && !root->right)) return; // 遇到空节点或叶子节点停止
        
        // 优先向右走，如果没有右孩子则向左走
        if (root->right) {
            addRightBoundary(root->right);
        } else {
            addRightBoundary(root->left);
        }
        
        // 递归返回时再加入当前节点值，实现逆序
        res.push_back(root->val); 
    }

public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        if (!root) return res;
        
        // 处理根节点：如果根不是叶子节点，先加入根节点
        if (root->left || root->right) {
            res.push_back(root->val);
        }
        
        // 分别按顺序求左边界、叶子节点、右边界
        addLeftBoundary(root->left);
        addLeaves(root);
        addRightBoundary(root->right);
        
        return res;
    }
};

// 辅助函数：根据输入构建树并返回根节点指针
TreeNode* buildTree() {
    int n;
    cin >> n;
    
    // 为了简单映射父节点到指针，我们使用一个数组暂存
    // 由于题目未明确说明节点值的范围上限，这里假设节点值在合理范围内（如0-10000）用于直接索引
    // 若节点值极大，可使用 map，但题意禁止使用STL树形结构，此处用大数组模拟哈希表
    const int MAX_VAL = 100005; 
    TreeNode* nodes[MAX_VAL] = {nullptr}; 

    for (int i = 0; i < n; ++i) {
        int parent, leftVal, rightVal;
        string lStr, rStr;
        
        cin >> parent >> lStr >> rStr;
        
        // 如果父节点尚未创建，则创建它
        if (nodes[parent] == nullptr) {
            nodes[parent] = new TreeNode(parent);
        }
        
        // 处理左孩子
        if (lStr != "#") {
            leftVal = stoi(lStr);
            if (nodes[leftVal] == nullptr) {
                nodes[leftVal] = new TreeNode(leftVal);
            }
            nodes[parent]->left = nodes[leftVal];
        }
        
        // 处理右孩子
        if (rStr != "#") {
            rightVal = stoi(rStr);
            if (nodes[rightVal] == nullptr) {
                nodes[rightVal] = new TreeNode(rightVal);
            }
            nodes[parent]->right = nodes[rightVal];
        }
    }
    
    // 第一行输入的父节点即为根节点，这里简化处理，假设第一个创建的节点为根
    // 实际严谨做法需记录第一行的parent
    // 重新读取第一行获取根节点值（或者在循环外单独读取）
    // 为了兼容上述逻辑，我们在主函数中先读取第一行
    
    // 注：上面的buildTree逻辑需要调整以正确捕获根节点，下面在主函数中完善
    return nullptr; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    
    const int MAX_VAL = 100005;
    TreeNode* nodes[MAX_VAL] = {nullptr};
    int rootVal = -1;

    for (int i = 0; i < n; ++i) {
        int parent, leftVal, rightVal;
        string lStr, rStr;
        
        cin >> parent >> lStr >> rStr;
        
        // 第一行即为根节点
        if (i == 0) rootVal = parent;
        
        if (nodes[parent] == nullptr) {
            nodes[parent] = new TreeNode(parent);
        }
        
        if (lStr != "#") {
            leftVal = stoi(lStr);
            if (nodes[leftVal] == nullptr) nodes[leftVal] = new TreeNode(leftVal);
            nodes[parent]->left = nodes[leftVal];
        }
        
        if (rStr != "#") {
            rightVal = stoi(rStr);
            if (nodes[rightVal] == nullptr) nodes[rightVal] = new TreeNode(rightVal);
            nodes[parent]->right = nodes[rightVal];
        }
    }

    Solution sol;
    vector<int> result = sol.boundaryOfBinaryTree(nodes[rootVal]);

    // 格式化输出，空格分隔，行首尾无多余空格
    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << endl;

    // 释放内存（可选，对于算法题通常省略，但养成好习惯）
    // 此处略去析构代码以保持核心逻辑清晰
    
    return 0;
}