/*
5. 压缩矩阵相乘
【问题描述】

    两个n阶整型对称矩阵A和B采用压缩存储方式，均按行优先顺序存放其下三角和主对角线的各元素。设计一个算法求A和B的乘积C，要求C直接用二维数组表示。
【输入形式】

第一行：输入对称矩阵阶数N

第二行：输入压缩后矩阵A

第三行：输入压缩后矩阵B
【输出形式】

第i行：输出矩阵C的第i行
【样例输入】

2

1 1 1

2 2 2
【样例输出】

4 4

4 4
【样例说明】

测试点中会出现负数
【评分标准】

A,B矩阵只能使用一维数组存储，使用非压缩二维数组存储不得分
*/

#include <iostream>
#include <vector>

using namespace std;

static inline long long getSymValue(const vector<long long>& compact, int n, int i, int j) {
    if (i < j) {
        int tmp = i;
        i = j;
        j = tmp;
    }
    int index = i * (i + 1) / 2 + j;
    return compact[index];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    int len = n * (n + 1) / 2;
    vector<long long> a(len), b(len);

    for (int i = 0; i < len; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < len; ++i) {
        cin >> b[i];
    }

    vector<vector<long long>> c(n, vector<long long>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            long long sum = 0;
            for (int k = 0; k < n; ++k) {
                sum += getSymValue(a, n, i, k) * getSymValue(b, n, k, j);
            }
            c[i][j] = sum;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j) {
                cout << ' ';
            }
            cout << c[i][j];
        }
        cout << '\n';
    }

    return 0;
}



