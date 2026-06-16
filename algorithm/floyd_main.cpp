#include <climits>
#include <stdio.h>
#include <stdlib.h>
#define MAXV 205

// 输出顶点u到顶点v的最短路径
void printPath(int Path[MAXV][MAXV], int u, int v) {
    // 从终点倒着推出每个点,先存到reversedPath数组中，最后倒着输出reversedPath数组即为最短路径
    int reversedPath[MAXV], step = 0;
    while (v != -1) {
        reversedPath[step++] = v;
        v = Path[u][v];
    }
    for (int i = step - 1; i >= 0; i--) {
        printf("%d ", reversedPath[i]);
    }
    printf("\n");
}

// Matrix为邻接矩阵，n为顶点数
void floyd(int Matrix[MAXV][MAXV], int n) {
    int Distance[MAXV][MAXV];    // 存任意两点的最短距离
    int Path[MAXV][MAXV]; // 存最短路径上终点的前一个点
    // 初始化Distance数组和path数组
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Distance[i][j] = Matrix[i][j];
            if (i != j && Matrix[i][j] != INT_MAX)
                Path[i][j] = i;
            else
                Path[i][j] = -1;
        }
    }
    // 依次将每个点作为中间点去做更新(floyd算法核心代码)
    for (int k = 0; k < n; k++) { // k代表中间点
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (Distance[i][k] != INT_MAX && Distance[k][j] != INT_MAX &&
                    Distance[i][k] + Distance[k][j] < Distance[i][j]) {
                    Distance[i][j] = Distance[i][k] + Distance[k][j];
                    Path[i][j] = Path[k][j];
                }
            }
        }
    }
    // 输出
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (Distance[i][j] != INT_MAX && i != j) {
                printf("从顶点%d到顶点%d的最短距离为:%d, 路径为:", i, j,
                       Distance[i][j]);
                printPath(Path, i, j);
            }
        }
    }
}

int main() {

    // 设置初始数据
    int Matrix[MAXV][MAXV] = {
        {0, INT_MAX, 5, 8}, {3, 0, 10, INT_MAX}, {INT_MAX, INT_MAX, 0, 4}, {7, 2, 11, 0}};
    int n = 4;

    // 利用floyd算法求任意两点的最短距离和最短路径
    floyd(Matrix, n);

    return 0;
}