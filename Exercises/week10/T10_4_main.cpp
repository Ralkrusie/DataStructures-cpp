/*
【问题描述】

   如图所示是一棵有根树，图中每个结点用1～16的整数标识，结点8是树根。如果结点x位于根结点到结点y之间的路径中，则结点x是结点y的祖先。如果结点x是结点y和结点z的祖先，则结点x称为两个不同结点y和z的公共祖先。如果x是y和z的共同祖先并且在所有共同祖先中最接近y和z，则结点x被称为结点y和z的最近公共祖先，如果y是z的祖先，那么y和z的最近共同祖先是y。例如结点16和7的最近公共祖先是结点4，结点2和3的最近公共祖先是结点10，结点4和12的最近公共祖先是结点4。编写一个程序，找到树中两个不同结点的最近公共祖先。

image.png

【输入形式】

  每个测试用例的第一行为树中结点数n（2≤n≤10,000），所有结点用整数1～n标识，接下来的n-1行中的每一行包含一对表示边的整数，第一个整数是第二个整数的父结点。请注意，具有n个结点的树具有恰好n-1个边。每个测试用例的最后一行为两个不同整数，需要计算它们的最近公共祖先。

【输出形式】

   为每个测试用例输出一行，该行应包含最近公共祖先结点的编号。

【样例输入】

16                                                                         

1 14

8 5

10 16

5 9

4 6

8 4

4 10

1 13

6 15

10 11

6 7

10 2

16 3

8 1

16 12

16 7

【样例输出】

4

【样例说明】

     测试数据的文件名为in.txt
*/


#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;

int main(){


   int n;
   std::ifstream fin("in.txt");
   while ( (fin >> n) ){
      vector<int> parent(n+1, 0);
      vector<vector<int>> children(n+1);

      for(int i = 0; i < n-1; ++i){
         int u, v; fin >> u >> v;
         parent[v] = u;
         children[u].push_back(v);
      }

      int a, b; fin >> a >> b;

      int root = 1;
      for(int i = 1; i <= n; ++i) if(parent[i] == 0){ root = i; break; }

      vector<int> depth(n+1, 0);
      // set depths by DFS from root
      stack<int> st;
      st.push(root);
      depth[root] = 0;
      while(!st.empty()){
         int u = st.top(); st.pop();
         for(int v: children[u]){
            depth[v] = depth[u] + 1;
            st.push(v);
         }
      }

      int x = a, y = b;
      // bring to same depth
      while(depth[x] > depth[y]) x = parent[x];
      while(depth[y] > depth[x]) y = parent[y];
      // climb until equal
      while(x != y){
         x = parent[x];
         y = parent[y];
      }

      cout << x << '\n';
   }

   return 0;
}








