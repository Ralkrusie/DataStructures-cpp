/*
2. 第八章第6题
【问题描述】

假设一个不带权连通图采用邻接表G存储，设计一个算法求距离顶点v的最短路径中最远的一个顶点。


【输入形式】

第一行输入邻接矩阵的维数n，接下来n行每行输入n个数字（0或1），为0代表不连通，为1代表连通；

第n+2行输入顶点v


【输出形式】

输出距离v的最短路径中最远的一个顶点；

如果v是孤立点（没有点和v相连），则输出-1


【样例输入1】

5

0 1 1 0 0

1 0 1 1 0

1 1 0 0 1

0 1 0 0 1

0 0 1 1 0

0


【样例输出1】

3 4



【样例1说明】

1到0的最短路径：1->0

2到0的最短路径：2->0

3到0的最短路径：3->1->0

4到0的最短路径：4->2->0

3和4一样远，故输出3 4



【样例输入2】

6

0 1 1 0 0 0

1 0 1 0 0 0

1 1 0 0 0 0

0 0 0 0 1 0

0 0 0 1 0 0

0 0 0 0 0 0

5



【样例输出2】

-1



【样例2说明】

5是孤立点，没有点和它相连，故输出-1
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> dijkstra(const vector<vector<int>>& adj, int n, int start) {
    vector<int> distance(n, -1);
    vector<bool> confirmed(n, false);

    //初始化
    distance[start] = 0;
    confirmed[start] = true;
    for (int neighbor : adj[start]) {
        distance[neighbor] = 1;
    }

    for (int i = 0; i < n; i++) {
        int minIndex = -1;
        int minDistance = -1;
        for (int j = 0; j < n; j++) {
            if (confirmed[j] == false) {
                if ((minDistance < 0 && distance[j] > 0) ||
                (distance[j] > 0 && distance[j] < minDistance)) {
                    minDistance = distance[j];
                    minIndex = j;
                }
            }
        }
        if (minDistance <= 0) {
            continue;
        }
        confirmed[minIndex] = true;
        for (int neighbor : adj[minIndex]) {
            if (!confirmed[neighbor]) {
                if (distance[neighbor] < 0 || distance[neighbor] > minDistance + 1) {
                    distance[neighbor] = minDistance + 1;
                }
            }
        }
    }
    return distance;
}




int main() {
    int n;
    cin >> n;
    vector<vector<int>> adj_G(n); 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int connected;
            cin >> connected;
            if (connected == 1) {
                adj_G[i].push_back(j);
            }
        }
    }
    int v;
    cin >> v;

    vector<int> distance = dijkstra(adj_G, n, v);

    int maxDistance = 0;
    vector<int> maxIndex;
    for (int i = 0; i < n; i++) {
        if (distance[i] > maxDistance) {
            maxDistance = distance[i];
            maxIndex.clear();
            maxIndex.push_back(i);
        } else if (distance[i] == maxDistance && distance[i] != 0) {
            maxIndex.push_back(i);
        }
    }
    if (maxIndex.empty()) {
        cout << "-1\n";
        return 0;
    }
    
    for (int i :maxIndex) {
        cout << i << ' ';
    }
    cout << endl;
    return 0;
}