/*
【问题描述】

一个图G采用邻接矩阵作为存储结构，设计一个算法采用广度优先遍历判断顶点i到顶点j是否有路径（假设顶点i和j都是G中的顶点）


【输入形式】

第一行输入邻接矩阵的维数n，接下来n行每行输入n个数字（0或1），为0代表不连通，为1代表连通；

第n+2行输入起始点i

第n+3行输入目的点j


【输出形式】

如果i到j有路径，那么输出TRUE；

如果没有，则输出FALSE


【样例输入1】

5

0 1 1 0 0

1 0 1 0 0

1 1 0 0 0

0 0 0 0 1

0 0 0 1 0

0

2


【样例输出2】

TRUE



【样例输入2】

5

0 1 1 0 0

1 0 1 0 0

1 1 0 0 0

0 0 0 0 1

0 0 0 1 0

0

4


【样例输出2】

FALSE


【考核说明】

题目要求使用广度优先遍历，用其他算法会酌情扣分
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool bfs(const vector<vector<int>>& matrix, int n, int start, int target) {
    vector<char> visited(n, 0);
    queue<int> qu;
    qu.push(start);
    while (!qu.empty()) {
        int current = qu.front();
        visited[current] = 1;
        qu.pop();
        for (int i = 0; i < n; i++) {
            if (matrix[current][i] == 1 && visited[i] == 0 ) {
                if (i == target) {
                    return true;
                }
                qu.push(i);
            }
        }
    }
    return false;
} 

int main() {
    int n;
    cin >> n;
    vector<vector<int>> matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int connected;
            cin >> connected;
            matrix[i].push_back(connected);
        }
    }
    int start, target;
    cin >> start >> target;

    if (bfs(matrix, n, start, target)) {
        cout << "TRUE\n";
        return 0;
    }
    cout << "FALSE\n";
    return 0;
}