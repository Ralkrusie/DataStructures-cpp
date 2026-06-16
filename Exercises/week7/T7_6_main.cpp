/*
【问题描述】


有一头母牛，它每年年初生一头小母牛。每头小母牛从第四个年头开始，每年年初也生一头小母牛。请编程实现在第n年的时候，共有多少头大小母牛？



【输入形式】

      输入一个整数n（0<n<55），n的含义如题目中描述。



【输出形式】


输出在第n年的时候大小母牛的数量。



【样例输入】

      5


【样例输出】

      6


【样例说明】

    第5年时共有6头母牛。测试数据存放在in.txt文件中。
*/

#include <iostream>
#include <vector>
#include <fstream>

int main() {
    int n;
    std::ifstream fin("in.txt");
    fin >> n;
    if (n == 1) {
        std::cout << 1 << '\n';
        return 0;
    } else if (n == 2) {
        std::cout << 2 << '\n';
        return 0;
    } else if (n == 3) {
        std::cout << 3 << '\n';
        return 0;
    }

    int m = n > 3 ? n : 3;
    std::vector<long long> matureCows(m, 0);
    for (int year = 1; year < 4; ++year) {
        matureCows[year-1] = 1;
    }
    // The number of cows born in year i is the number of mature cows in year i.
    for (int year = 4; year <= m; ++year) {
        matureCows[year-1] = matureCows[year-1 - 1] + matureCows[year-1 - 3];
    }

    int total = matureCows[n-1] + matureCows[n-1 - 1] + matureCows[n-1 - 2];
    std::cout << total << '\n';
    return 0;
}