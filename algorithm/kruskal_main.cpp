#include <stdio.h>
#include <stdlib.h>

#define MAXV 500
#define MAXE 100

struct Edge {
    int u, v; // 边的两个端点
    int w;    // 边的权值
};

// 归并排序部分
void merge(Edge E[], int left, int mid, int right) {
    Edge *temp = (Edge *)malloc((right - left + 1) * sizeof(Edge));
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (E[i].w <= E[j].w) {
            temp[k++] = E[i++];
        } else {
            temp[k++] = E[j++];
        }
    }
    while (i <= mid)
        temp[k++] = E[i++];
    while (j <= right)
        temp[k++] = E[j++];
    for (i = left, k = 0; i <= right; i++, k++)
        E[i] = temp[k];
    free(temp);
}

void mergeSort(Edge E[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(E, left, mid);
        mergeSort(E, mid + 1, right);
        merge(E, left, mid, right);
    }
}

// 并查集的find操作
int find(int parent[], int x) {
    if (parent[x] == x)
        return x;
    else
        return parent[x] = find(parent, parent[x]);
}

// E-边数组,n-顶点数,m-边数
// 返回最小生成树的边权和
int kruskal(Edge E[], int n, int m) {
    int parent[MAXV];             // 并查集数组
    int sum = 0;                  // 保存最小生成树的边权和
    int count = 0;                // 用于数加入了几条边
    mergeSort(E, 0, m - 1);       // 对边数组从小到大排序
    for (int i = 0; i < n; i++) { // 并查集初始化
        parent[i] = i;
    }
    for (int i = 0; i < m; i++) { // 依次枚举每条边
        // 查看两个端点是否属于同一个连通分量
        int parentu = find(parent, E[i].u); // 找u所属的连通分量
        int parentv = find(parent, E[i].v); // 找v所属的连通分量
        if (parentu != parentv) {           // 如果不在同一个连通分量
            parent[parentv] = parentu;      // 合并
            sum += E[i].w;                  // 累加边权
            count++;
            if (count == n - 1)
                break; // 当加入n-1条边后结束循环
        }
    }
    if (count != n - 1)	// 图不连通
        return -1;	
    return sum;
}

int main() {

    // 直接初始化的方式
    Edge E[] = {{0, 1, 14}, {0, 2, 1}, {0, 3, 6}, {1, 2, 3},  {1, 4, 2},
                {2, 3, 8},  {2, 4, 5}, {2, 5, 9}, {3, 5, 12}, {4, 5, 10}};
    int n = 6;
    int m = 10;

    // 输入的方式
    //	Edge E[MAXE];//边数组
    //	int n,m;//n为顶点数，m为边数
    //	scanf("%d %d",&n,&m);
    //	for(int i=0;i<m;i++){//将每条边的信息输入到E数组
    //		scanf("%d %d %d",&E[i].u,&E[i].v,&E[i].w);
    //	}

    // 使用kruskal算法求最小生成树的边权和
    int sum = kruskal(E, n, m);

    // 输出
    if (sum == -1)
        printf("图不连通");
    else
        printf("%d", sum);

    return 0;
}