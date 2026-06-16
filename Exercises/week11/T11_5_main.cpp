/*
一、问题描述
给定一个无向图，判断该图是否是连通图。如果是连通图，输出"YES"；否则输出"NO"，并输出连通分量的数量。

二、输入形式
第一行输入两个正整数n和m（1 ≤ n ≤ 1000, 0 ≤ m ≤ 10000），表示节点数和边数。
接下来m行，每行两个整数u和v，表示节点u和v之间有一条边。

三、输出形式
如果是连通图，输出"YES"。
如果不是连通图，输出"NO"和连通分量数量，用空格分隔。

四、样例输入1

6 7
1 2
1 3
2 4
2 5
3 5
4 6
5 6
五、样例输出1

YES
六、样例输入2

5 2
1 2
3 4
七、样例输出2

NO 3
八、样例说明
样例1：所有节点都连通，是连通图。
样例2：连通分量有{1,2}、{3,4}、{5}，共3个，不是连通图。

九、评分标准
共6个测试用例。

十、类库使用要求
可以使用vector、queue。使用DFS或BFS遍历。
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(const vector<vector<int>> &adj, vector<bool> &visited, int start)
{
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : adj[u])
        {
            if (!visited[v])
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(n + 1, false);
    int components = 0;

    for (int i = 1; i <= n; ++i)
    {
        if (!visited[i])
        {
            ++components;
            bfs(adj, visited, i);
        }
    }

    if (components == 1)
        cout << "YES" << endl;
    else
        cout << "NO " << components << endl;

    return 0;
}