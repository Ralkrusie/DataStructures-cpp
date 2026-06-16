/*
【问题描述】


阿里本学期开设了计算机组织与架构课程，他了解到指令之间可能存在依赖关系，如WAR（写入后读取），WAW，RAW。如果两个指令之间的距离小于安全距离（Safe Distances），则会导致危险，这可能导致错误的结果，所以需要设计特殊的电路以消除危险。然而，解决此问题的最简单方法是添加气泡（无用操作），这意味着浪费时间以确保两条指令之间的距离不小于安全距离。

两条指令之间距离的定义是它们的开始时间之间的差异。现在有很多指令，已知指令之间的依赖关系和安全距离。我们有一个非常强大的CPU，具有无限数量的内核，因此你可以根据需要同时运行多个指令，并且CPU速度非常快，只需花费1ns即可完成任何指令。你的工作是重新排列指令，以便CPU可以使用最短的时间完成所有指令。



【输入形式】


输入包含几个测试用例。每个测试用例的第一行是两个整数n，m（n≤1000，m≤10000），表示有n个指令和m个依赖关系，以下m行，每行包含三个整数x，y，z，表示x和y之间的安全距离为z，y应在x之后运行。指令编号从0到n-1。



【输出形式】


输出一个整数，即CPU运行所需的最短时间。



【样例输入】

         5 2

         1 2 1

  3 4 1



【样例输出】


  2



【样例说明】

      输入样例有5个指令，2个依赖关系，CPU运行所需的最短时间为2。测试数据存放在in.txt文件中。


【评分标准】

        共10个测试用例，每通过一个测试得10分。
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("in.txt");
    int n, m;
    while (fin >> n >> m) {
        vector<vector<pair<int, int>>> adj(n);
        vector<int> indeg(n, 0);

        for (int i = 0; i < m; ++i) {
            int x, y, z;
            fin >> x >> y >> z;
            adj[x].emplace_back(y, z);
            indeg[y]++;
        }

        // 拓扑排序 + DP 求每个指令的最早开始时间
        vector<int> dist(n, 0);
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &[v, w] : adj[u]) {
                if (dist[u] + w > dist[v]) {
                    dist[v] = dist[u] + w;
                }
                if (--indeg[v] == 0) {
                    q.push(v);
                }
            }
        }

        // 每个指令执行需要 1ns，总时间 = max(开始时间 + 1)
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, dist[i] + 1);
        }
        cout << ans << endl;
    }
    return 0;
}