/*
[问题描述】

    给定一棵二叉树，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的结点值。例如，如图下图所示的二叉树的输出结果是[1，3，4]。二叉树节点数据为正整数，数值不超过100000，节点个数不超过100。

image.png

【输入形式】输入为一行数据，是二叉树的括号表示法的字符串。

【输出形式】输出为一行数据，右视图的结果放在方括号中，每个节点数据之间用“，”隔开
【样例输入】

1（2（，5），3（，4））

【样例输出】[1，3，4]

【样例说明】
     测试数据的文件名为in.txt
*/


#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <queue>
#include <string>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v): val(v), left(nullptr), right(nullptr){}
};

string normalize(const string &s){
    string t;
    for(char c: s){
        if(c == '（') t.push_back('(');
        else if(c == '）') t.push_back(')');
        else if(c == '，') t.push_back(',');
        else if(!isspace((unsigned char)c)) t.push_back(c);
    }
    return t;
}

TreeNode* parseNode(const string &s, int &i){
    int n = s.size();
    if(i >= n) return nullptr;
    // expect a number
    if(!isdigit((unsigned char)s[i])) return nullptr;
    int val = 0;
    while(i < n && isdigit((unsigned char)s[i])){
        val = val*10 + (s[i]-'0');
        ++i;
    }
    TreeNode* node = new TreeNode(val);
    if(i < n && s[i] == '('){
        ++i; // consume '('
        // parse left
        if(i < n && s[i] == ','){
            node->left = nullptr;
        } else {
            node->left = parseNode(s, i);
        }
        // now expect comma
        if(i < n && s[i] == ',') ++i; // consume comma
        // parse right
        if(i < n && s[i] == ')'){
            node->right = nullptr;
        } else {
            node->right = parseNode(s, i);
        }
        // consume closing ')'
        if(i < n && s[i] == ')') ++i;
    }
    return node;
}

vector<int> rightSideView(TreeNode* root){
    vector<int> res;
    if(!root) return res;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int sz = q.size();
        for(int i=0;i<sz;++i){
            TreeNode* cur = q.front(); q.pop();
            if(i==sz-1) res.push_back(cur->val);
            if(cur->left) q.push(cur->left);
            if(cur->right) q.push(cur->right);
        }
    }
    return res;
}

int main(){
    std::ifstream fin("in.txt");
    string line;
    if(!std::getline(fin, line)) return 0;
    string s = normalize(line);
    if(s.empty()){
        cout << "[]\n";
        return 0;
    }
    int idx = 0;
    TreeNode* root = parseNode(s, idx);
    vector<int> view = rightSideView(root);
    // output as [a,b,c]
    cout << '[';
    for(size_t i=0;i<view.size();++i){
        if(i) cout << ',';
        cout << view[i];
    }
    cout << "]\n";
    return 0;
}















