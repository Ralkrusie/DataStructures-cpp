/*
【问题描述】


杭州有n个景区，景区之间有一些双向的路来连接，现在万先生想找一条旅游路线，这个路线从A点出发并且最后回到A点，假设经过的路线为v1，v2，…，vk，v1，那么必须满足k>2，就是说至除了出发点以外至少要经过两个其他不同的景区，而且不能重复经过同一个景区。现在万先生需要你帮他找一条这样的路线，并且花费越少越好。





【输入形式】

        第一行是两个整数n和m（n≤100，m≤1000)，代表景区的个数和道路的条数。接下来的m行每行包括3个整数a，b，c，代表a和b之间有一条通路，并且需要花费c元（c≤100）。



【输出形式】


对于每个测试用例，如果能找到这样一条路线的话，输出花费的最小值。如果找不到的话，输出"It's impossible."。



【样例输入】




3 3

1 2 1

2 3 1

1 3 1



【样例输出】



     3


【样例说明】

       输入的数据包含3个景区和3条道路，可以找到一条旅游路线，其最小代价为3。测试数据存放在in.txt文件中。


【评分标准】

        共10个测试用例，每通过一个测试得10分。
*/

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

int main(){
        ifstream fin("in.txt");
        int n, m;
        if(!(fin >> n >> m)) return 0;
        const int INF = 1e9;
        struct Edge{int to,w,id;};
        vector<vector<Edge>> g(n+1);
        vector<tuple<int,int,int>> edges;
        edges.reserve(m);
        for(int i=0;i<m;i++){
                int a,b,c; fin >> a >> b >> c;
                edges.emplace_back(a,b,c);
                g[a].push_back({b,c,i});
                g[b].push_back({a,c,i});
        }

        int answer = INF;

        // 对每条边 i，暂时禁止该边（通过比较边 id），在剩余图上找从 u 到 v 的最短简单路径且边数 >=2
        for(int i=0;i<m;i++){
                int u,v,w; tie(u,v,w) = edges[i];

                // 标准 Dijkstra：从 u 到 v（跳过被删除的边 id==i）
                vector<int> dist(n+1, INF);
                priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq2;
                dist[u] = 0;
                pq2.emplace(0,u);
                while(!pq2.empty()){
                    auto [d,x] = pq2.top(); pq2.pop();
                    if(d != dist[x]) continue;
                    for(const auto &e: g[x]){
                        if(e.id == i) continue; // 禁止当前边
                        int y = e.to;
                        int nd = d + e.w;
                        if(nd < dist[y]){
                            dist[y] = nd;
                            pq2.emplace(nd, y);
                        }
                    }
                }
                if(dist[v] < INF){
                    // 因为题目无重边，自环，移除当前边后若存在路径则至少包含2条边，构成长度>2的环
                    answer = min(answer, dist[v] + w);
                }
        }

        if(answer == INF) cout << "It's impossible.";
        else cout << answer;

        return 0;
}

