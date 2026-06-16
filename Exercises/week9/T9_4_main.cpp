/*
4. 第八章第4题
【问题描述】
给定一个无向图 G，该图采用邻接表作为其存储结构。设计一个算法，计算并返回图 G 中连通分量的数量。连通分量定义为图中所有相互连通的顶点的最大子集，在无向图中，任意两个顶点之间都存在路径相连。

【输入形式】
输入包括两部分：

第一行包含两个整数 V 和 E，分别表示图中的顶点数和边数，其中 V≥1，E≥0。

接下来的 E 行，每行包含两个整数 u 和 v，表示顶点 u 和顶点 v 之间存在一条无向边。顶点编号从 1 到 V

【输出形式】
输出一个整数，表示图 G 中连通分量的数量。



【样例输入】

7 5
1 2
1 3
2 3
4 5
6 7
【样例输出】

3
【解释】
在给定的图中，有 7 个顶点和 5 条边，形成了以下连通分量：

顶点 1、2、3相互连通，形成一个连通分量。

顶点 4、5相互连通，形成第二个连通分量。

顶点 6、7 相互连通，形成第三个连通分量。
因此，图中共有 3 个连通分量。

【注意】

不是 O(nlogn) 以内的算法的话，可能会超时的呦！
*/

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;


int main() {
    int V, E;
    cin >> V >> E;
    unordered_map<int, vector<int>> adj;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        //cout << u << ' ' << v << endl;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int components = 0;
    stack<int> st;
    unordered_map<int, bool> visited(false);
    for (int i = 0; i < V; i++) {
        if (visited[i] == 0) {
            st.push(i);
            visited[i] = 1;
            components++;
            while (!st.empty()) {
                int current = st.top();
                st.pop();
                for (int neighbor : adj[current]) {
                    if (visited[neighbor] == 0) {
                        st.push(neighbor);
                        visited[neighbor] = 1;
                    }
                }
            }
        }
    }
    cout << components;
}

/*
我们的题目还要不要为人民服务？我们的题目还要不要为学生服务？要不要为老师服务？它是一个人民的题目吗？今天，我在这个希冀平台，数据结构A的这个课程，做了一道关于连通分量的题目。这个题目，在题干中，它说是顶点编号从1到V。但是在这个光鲜的表面的背后，是背信弃义的恶劣行为！我把这个编号我std::cout出来啊，我立马就观测到，它下面的全都是这个恶劣的，不知道是随机数还是什么东西。它背信弃义，它说是从1到V。这个从1到V，按道理来说，是顶点的编号。它拿这些胡乱的编号，压迫坑害我们的学生，坑害我们的老师，坑害我们的人民！我们还要它这个东西干什么？！不把它给它开除掉，不把它赶出题库，我们的助教还在等什么？我们有这样反动的题目，学生有好过的日子吗？我们的学生有好生的日子吗？这就是这些恶劣的题目，走向衰败和灭亡的前兆！我们一定要把这个恶劣的题目的环境，一定要整改它，你不把它整改，你不把这些恶劣的出题人赶出去，学生没用光明的未来，我们的学校没有光明的未来！
*/