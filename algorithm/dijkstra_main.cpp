#include <stdio.h>
#include<stdlib.h>
#include <climits>

#define MAXV 100


// 输出源点到顶点goal的最短路径
void PrintPath(int pre[], int goal) {
    // 从终点倒着推出每个点,先存到temp数组中，最后倒着输出temp数组即为最短路径
    int reversedPath[MAXV], step = 0;
    while (goal != -1) {
        reversedPath[step++] = goal;
        goal = pre[goal];
    }
    for (int i = step - 1; i >= 0; i--) {
        printf("%d ", reversedPath[i]);
    }
    printf("\n");
}

// matrix为邻接矩阵，n为顶点数, start为源点
void dijkstra(int matrix[MAXV][MAXV], int n, int start) {
    int distance[MAXV];  // 存源点start到每个点的最短距离
    bool comfirmed[MAXV]; // 标记每个点是否已确定最短距离
    int pre[MAXV];   // 存每个点在最短路径上的前一个点
    for (int i = 0; i < n; i++) { // 初始化
        distance[i] = matrix[start][i];
        comfirmed[i] = false;
        if (matrix[start][i] < INT_MAX)
            pre[i] = start;
        else
            pre[i] = -1;
    }
    comfirmed[start] = true;                  // 源点最开始就已确定
    distance[start] = 0;                  // 源点到自己的最短距离为0
    for (int i = 1; i < n; i++) { // 再找n-1个点
        // 每次都找距离源点start最近的点
        int minDistance = INT_MAX; // 存最小值
        int minIndex = -1;        // 最小值对应哪个点
        for (int j = 0; j < n; j++) {
            if (comfirmed[j] == false && distance[j] < minDistance) {
                minDistance = distance[j];
                minIndex = j;
            }
        }
        if (minDistance == INT_MAX)
            break; // start不可达剩余的点
        // 将顶点minIndex标记为已确定
        comfirmed[minIndex] = true;
        // 看看源点通过minIndex到其余点的距离会不会更短
        for (int j = 0; j < n; j++) {

            if (comfirmed[j] == false && matrix[minIndex][j] < INT_MAX && distance[minIndex] + matrix[minIndex][j] < distance[j]) {
                distance[j] = distance[minIndex] + matrix[minIndex][j];
                pre[j] = minIndex;
            }
        }
    }
    // 输出
    for (int i = 0; i < n; i++) {
        if (comfirmed[i] == 0) {
            printf("源点%d到顶点%d不可达\n", start, i);
        } else {
            printf("源点%d到顶点%d的最短距离为:%d，路径为:", start, i, distance[i]);
            PrintPath(pre, i);
        }
    }
}

int main() {

    // 设置初始数据
    int n = 6;
    int matrix[MAXV][MAXV] = {
        {INT_MAX, 5, 3, INT_MAX, INT_MAX, INT_MAX},   {INT_MAX, INT_MAX, INT_MAX, 3, 4, INT_MAX},
        {INT_MAX, 1, INT_MAX, 2, 6, INT_MAX},     {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 7, 2},
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 1}, {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX}};

    // 利用dijminIndexstra算法求顶点0到其余点的最短距离和最短路径
    dijkstra(matrix, n, 0);

    return 0;
}