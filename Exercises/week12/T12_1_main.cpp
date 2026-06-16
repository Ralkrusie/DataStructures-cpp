/*
【问题描述】

假设一个有向图采用邻接表 G作为存储结构。设计一个算法，输出从顶点 u 到顶点 v 的所有不经过顶点 w 的简单路径。

所谓简单路径，是指路径中所有顶点不重复出现。

路径不能经过顶点 w，但允许从 u 到 v 是直接相连（只要不包含 w）。

【输入形式】

第一行输入四个整数：n m u v w

n 表示图中顶点个数（顶点编号为 0~n-1）

m 表示边数

u 表示起点

v 表示终点

w 表示不能经过的顶点编号

接下来 m 行，每行输入两个整数 a b，表示一条从 a 到 b 的有向边。

【输出形式】

每行输出一条路径，从起点 u 到终点 v，格式为：

 u1 u2 u3  ...  v 每个节点之间空一格

若没有路径，输出-1

【样例输入】

6 7 0 5 3

0 1

1 2

2 5

0 4

4 5

1 3

3 5

【样例输出】

0 1 2 5

0 4 5

【样例说明】

路径 0 → 1 → 3 → 5 被排除，因为中间包含禁止顶点 3
*/

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

vector<vector<int>> findAllPaths(const vector<vector<int>>& adj, int n, int start, int target) {
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> visited(n, false);

    function<void(int)> dfs = [&](int cur) {
        visited[cur] = true;
        path.push_back(cur);

        if (cur == target) {
            result.push_back(path);
        } else {
            for (int neighbor : adj[cur]) {
                if (!visited[neighbor]) {
                    dfs(neighbor);
                }
            }
        }

        path.pop_back();
        visited[cur] = false;
    };

    dfs(start);
    return result;
}

int main() {
    int n, m, u, v, w;
    cin >> n >> m >> u >> v >> w;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (a == w || b == w) {
            continue;
        }
        adj[a].push_back(b);
    }

    vector<vector<int>> paths = findAllPaths(adj, n, u, v);

    if (paths.empty()) {
        cout << -1 << endl;
    } else {
        for (const auto& p : paths) {
            for (size_t i = 0; i < p.size(); i++) {
                if (i > 0) cout << ' ';
                cout << p[i];
            }
            cout << endl;
        }
    }

    return 0;
}
