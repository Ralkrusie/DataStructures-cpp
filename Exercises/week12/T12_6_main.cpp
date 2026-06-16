/*
【问题描述】


有N个网络结点，标记为1到N。给定一个列表times，表示信号经过有向边的传递时间，times[i]=(u，v，w)，其中u是源结点，v是目标结点，w是一个信号从源结点传递到目标结点的时间。现在我们向当前的结点K发送了一个信号，需要多久才能使所有结点都收到信号？如果不能使所有结点收到信号，返回-1。这里N的范围在[1，100]之间，K的范围在[1，N]之间，times的长度在[1，6000]之间，所有的边times[i]=(u，v，w)都有1≤u，v≤N且0≤w≤100。




要求设计满足题目要求的函数：

class Solution {
public:
 int networkDelayTime(vector<vector<int>>& times,int N,int K)
 {  …  }
};




【输入形式】

   输入网络结点的总个数N，以及信号发送的起始结点K。 然后输入时间列表，其中每一行给出了源结点、目标结点以及信号从源结点到目标结点锁需要的时间。


【输出形式】

    输出所有结点都收到信号需要花费的时间。



【样例输入】


4 2
2 1 1
2 3 1
3 4 1
【样例输出】

    2


【样例说明】
    测试数据存放在in.txt文件中。
【评分标准】

    共10个测试用例，每通过一个测试得10分。
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <climits>

using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        const int INF = 1e9;
        // 邻接表
        vector<vector<pair<int, int>>> adj(N);
        for (auto &t : times) {
            int u = t[0] - 1, v = t[1] - 1, w = t[2];
            adj[u].emplace_back(v, w);
        }

        // Dijkstra
        vector<int> dist(N, INF);
        dist[K - 1] = 0;
        // 小根堆 (d, v)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.emplace(0, K - 1);

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if (d != dist[u]) continue;
            for (size_t i = 0; i < adj[u].size(); ++i) {
                int v = adj[u][i].first;
                int w = adj[u][i].second;
                if (d + w < dist[v]) {
                    dist[v] = d + w;
                    pq.emplace(dist[v], v);
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < N; ++i) {
            if (dist[i] == INF) return -1;
            if (dist[i] > ans) ans = dist[i];
        }
        return ans;
    }
};

int main() {
    ifstream fin("in.txt");
    int N, K;
    fin >> N >> K;
    vector<vector<int>> times;
    int u, v, w;
    while (fin >> u >> v >> w) {
        times.push_back({u, v, w});
    }

    Solution sol;
    cout << sol.networkDelayTime(times, N, K) << endl;
    return 0;
}