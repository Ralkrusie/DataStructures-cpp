/*
第八章第8题
【问题描述】

假设一个无向图采用邻接表G作为存储结构，设计一个算法判断其中是否存在经过顶点v的简单回路（环）。


【输入形式】

第一行输入邻接矩阵的维数n，接下来n行每行输入n个数字（0或1），为0代表不连通，为1代表连通；

第n+2行输入顶点v


【输出形式】

如果有经过顶点v的简单回路，输出TRUE

否则输出FALSE


【样例输入1】

4

0 1 0 1

1 0 1 0

0 1 0 0

1 0 0 0

0


【样例输出1】

FALSE



【样例输入2】

4 

0 1 0 1

1 0 1 1

0 1 0 1

1 1 1 0

0



【样例输出2】

TRUE


*/

#include <iostream>
#include <vector>
#include <list>

using namespace std;

/**
 * DFS 判断从 current 出发能否到达 target，过程中不经过 excluded 顶点。
 */
static bool dfs(const vector<list<int>> &adj, vector<bool> &visited,
                int current, int target, int excluded)
{
    if (current == target)
        return true;

    visited[current] = true;
    for (int nb : adj[current])
    {
        if (nb == excluded)
            continue; // 不允许走回 excluded 顶点
        if (!visited[nb])
        {
            if (dfs(adj, visited, nb, target, excluded))
                return true;
        }
    }
    return false;
}

/**
 * 判断无向图 adj 中是否存在经过顶点 v 的简单回路。
 *
 * 思路：
 *   简单回路形如 v → u → … → w → v，其中 u、w 是 v 的两个不同邻接点，
 *   且 u 到 w 有一条不经过 v 的路径。
 *
 *   因此只需枚举 v 的任意两个不同邻接点 u、w，检查 u 能否不经过 v 到达 w。
 */
static bool hasCycleThroughV(const vector<list<int>> &adj, int v)
{
    int n = (int)adj.size();

    // 收集 v 的所有邻接点
    vector<int> neighbors;
    for (int nb : adj[v])
        neighbors.push_back(nb);

    // 枚举每一对不同的邻接点 (u, w)
    for (size_t i = 0; i < neighbors.size(); ++i)
    {
        for (size_t j = i + 1; j < neighbors.size(); ++j)
        {
            int u = neighbors[i];
            int w = neighbors[j];
            vector<bool> visited(n, false);
            visited[v] = true; // 禁止走回 v
            // 从 u 出发搜索是否能到达 w
            if (dfs(adj, visited, u, w, v))
                return true;
        }
    }
    return false;
}

int main()
{
    int n;
    cin >> n;

    // 读入邻接矩阵
    vector<vector<int>> mat(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> mat[i][j];

    int v;
    cin >> v;

    // 将邻接矩阵转换为邻接表
    vector<list<int>> adj(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (mat[i][j] == 1)
                adj[i].push_back(j);

    cout << (hasCycleThroughV(adj, v) ? "TRUE" : "FALSE") << endl;

    return 0;
}