/*
【问题描述】

一个连通图采用邻接表作为存储结构，设计一个算法实现从顶点v出发的深度优先遍历的非递归与递归过程。


【输入形式】

第一行输入邻接矩阵的维数n，接下来n行每行输入n个数字（0或1），为0代表不连通，为1代表连通；

第n+2行输入顶点v


【输出形式】

第一行输出非递归过程遍历结果；

第一行输出递归过程遍历结果；


【样例输入1】

5

0 1 0 1 0

0 0 1 1 0

0 0 0 1 1

0 0 0 0 0

1 0 0 1 0

0


【样例输出1】

0 1 2 3 4

0 1 2 3 4



【样例说明】

由于输出的结果唯一，那么优先探索的顺序需要按照邻接表的顺序，不然会有多个结果



【考核说明】

全用递归过程而没有非递归过程会酌情扣分；

要求使用深度优先遍历


*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int>> buildAdjList(const vector<vector<int>> &mat, int n)
{
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (mat[i][j] == 1)
                adj[i].push_back(j); // i 自然递增，邻居已按 j 升序
    return adj;
}

void dfsRecursive(const vector<vector<int>> &adj, vector<bool> &visited, int v)
{
    visited[v] = true;
    cout << v << " ";
    for (int u : adj[v])
        if (!visited[u])
            dfsRecursive(adj, visited, u);
}

void dfsIterative(const vector<vector<int>> &adj, int start)
{
    int n = (int)adj.size();
    vector<bool> visited(n, false);
    stack<int> st;
    st.push(start);

    while (!st.empty())
    {
        int v = st.top();
        st.pop();

        if (visited[v])
            continue;

        visited[v] = true;
        cout << v << " ";

        for (auto it = adj[v].rbegin(); it != adj[v].rend(); ++it)
            if (!visited[*it])
                st.push(*it);
    }
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> mat(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> mat[i][j];

    int v;
    cin >> v;

    auto adj = buildAdjList(mat, n);

    dfsIterative(adj, v);
    cout << endl;

    vector<bool> visited(n, false);
    dfsRecursive(adj, visited, v);
    cout << endl;

    return 0;
}