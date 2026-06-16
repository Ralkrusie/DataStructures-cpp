/*
【问题描述】

    给你二叉树的根结点root、树中一个结点target和一个正整数k，求二叉树中距离target结点为k的所有结点。假设二叉树中的所有结点值都唯一。输入为顺序存储方式表示的二叉树字符串，如果节点为空，则输入‘#’。

  例如，输入root=[3，5，1，6，2，0，8，#，#，7，4]，target=5，k=2，输出为[7，4，1]。对应的二叉树如图所示。

image.png





   其中离目标结点5的距离为2的结点是7、4、1。假设给定的二叉树非空，树中每个结点有唯一值，结点值位于0到500之间，target是其中的一个结点，0≤k≤1000。

要求设计如下成员函数：

class Solution {

public:

          vector<int> distanceK(TreeNode* root, TreeNode* target, int k)

          {  …   }

};

【输入形式】

       每个测试用例由三行，第一行是由一对方括号[]括起来的顺序存储的二叉树节点数据，每个节点用“,”隔开，如果是空节点，则存入“#”。第二行为目标节点数据，第三行为距离。

【输出形式】

     用一对方括号[]将满足要求的节点括起来后输出，如有多个节点，用“，”隔开，节点输出顺序：优先输出目标节点的子孙节点，其次是目标节点兄弟节点的子孙节点，最后是目标节点的祖父节点（如果有多个祖父节点的子孙节点，则从最近的开始输出），如果在同一层从左边到右边输出。

【样例输入】


[1,2,3,4,5,6,7,8,9,10,11,12,13,#,#,14,15,16,17,18,19,#,#,#,#,#,#,#,#,#,#,20,21,22,23,24,25,26,27]

4

3

【样例输出】

[20,21,22,23,10,11,3]

【样例说明】

     测试数据的文件名为in.txt
*/

#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct TreeNode{
     int val;
     TreeNode* left;
     TreeNode* right;
     TreeNode(int v): val(v), left(nullptr), right(nullptr){}
};

static inline string trim(const string &s){
     size_t a = 0, b = s.size();
     while(a < b && isspace((unsigned char)s[a])) ++a;
     while(b > a && isspace((unsigned char)s[b-1])) --b;
     return s.substr(a, b-a);
}

vector<string> splitTokens(const string &s){
     vector<string> res;
     string cur;
     for(char c: s){
          if(c==','){
               res.push_back(trim(cur)); cur.clear();
          } else cur.push_back(c);
     }
     if(!cur.empty()) res.push_back(trim(cur));
     return res;
}

TreeNode* buildTreeFromLevel(const vector<string>& tokens, vector<TreeNode*> &nodes, unordered_map<TreeNode*, TreeNode*>& parent){
     int n = tokens.size();
     nodes.assign(n, nullptr);
     for(int i=0;i<n;++i){
          if(tokens[i] != "#" && !tokens[i].empty()){
               int v = stoi(tokens[i]);
               nodes[i] = new TreeNode(v);
          }
     }
     for(int i=0;i<n;++i){
          if(!nodes[i]) continue;
          int l = 2*i+1;
          int r = 2*i+2;
          if(l < n && nodes[l]){ nodes[i]->left = nodes[l]; parent[nodes[l]] = nodes[i]; }
          if(r < n && nodes[r]){ nodes[i]->right = nodes[r]; parent[nodes[r]] = nodes[i]; }
     }
     return n>0 ? nodes[0] : nullptr;
}

vector<int> distanceK(TreeNode* root, TreeNode* target, unordered_map<TreeNode*, TreeNode*> &parent, int K){
     vector<int> res;
     if(!root || !target) return res;
     unordered_set<TreeNode*> visited;
     queue<TreeNode*> q;
     q.push(target);
     visited.insert(target);
     int dist = 0;
     while(!q.empty()){
          int sz = q.size();
          if(dist == K){
               // collect current level in queue order
               while(sz--){
                    TreeNode* node = q.front(); q.pop();
                    res.push_back(node->val);
               }
               return res;
          }
          for(int i=0;i<sz;++i){
               TreeNode* cur = q.front(); q.pop();
               // enqueue left then right then parent to match required ordering
               if(cur->left && !visited.count(cur->left)){
                    visited.insert(cur->left);
                    q.push(cur->left);
               }
               if(cur->right && !visited.count(cur->right)){
                    visited.insert(cur->right);
                    q.push(cur->right);
               }
               auto it = parent.find(cur);
               if(it != parent.end()){
                    TreeNode* p = it->second;
                    if(p && !visited.count(p)){
                         visited.insert(p);
                         q.push(p);
                    }
               }
          }
          ++dist;
     }
     return res;
}

int main(){
     ios::sync_with_stdio(false);
     cin.tie(nullptr);

     // Prefer reading from in.txt if present, otherwise stdin
     ifstream fin("in.txt");
     istream &in = fin && fin.good() ? fin : cin;

     string line;
     // read three non-empty lines
     string treeLine;
     while(getline(in, line)){
          line = trim(line);
          if(!line.empty()){ treeLine = line; break; }
     }
     if(treeLine.empty()) return 0;

     string targetLine;
     while(getline(in, line)){
          line = trim(line);
          if(!line.empty()){ targetLine = line; break; }
     }
     string kLine;
     while(getline(in, line)){
          line = trim(line);
          if(!line.empty()){ kLine = line; break; }
     }

     // parse treeLine like [1,2,3,#,...]
     string content = treeLine;
     if(!content.empty() && content.front()=='[' && content.back()==']') content = content.substr(1, content.size()-2);
     vector<string> tokens = splitTokens(content);
     vector<TreeNode*> nodes;
     unordered_map<TreeNode*, TreeNode*> parent;
     TreeNode* root = buildTreeFromLevel(tokens, nodes, parent);

     int targetVal = stoi(targetLine);
     int K = stoi(kLine);

     TreeNode* target = nullptr;
     for(TreeNode* nd: nodes) if(nd && nd->val == targetVal){ target = nd; break; }

     vector<int> ans = distanceK(root, target, parent, K);

     // output with ordering: ans already ordered by BFS neighbor enqueue sequence
     cout << '[';
     for(size_t i=0;i<ans.size();++i){ if(i) cout << ','; cout << ans[i]; }
     cout << "]\n";

     return 0;
}

