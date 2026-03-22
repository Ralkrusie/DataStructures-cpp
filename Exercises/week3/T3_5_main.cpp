/*
【问题描述】定义三元组(a,b,c)(a,b,c均为整数)的距离D=|a-b|+|b-c|+|c-a|。给定3个非空整数集合S1、S2和S3，集合大小分别为n,m,k，分别存储在3个数组中。设a,b,c分别为S1,S2,S3中的元素，试计算并输出最小的D。

【输入形式】第一行包含三个整数n,m,k,分别代表S1,S2,S3的大小

           第二行包含n个整数。

           第三行包含m个整数。

           第四行包含k个整数。

【输出形式】仅包含一个数Dmin，代表所有D值中最小的值。

【样例输入】3 4 5

           -1 0 9

           -25 -10 10 11

           2 9 17 30 41
【样例输出】2

【样例说明】使D最小的三元组是(9,10,9)

【数据范围】0<n,m,k≤10000，对所有集合内的元素ai满足-1e7<ai<1e7

【评分标准】共10个测试数据，每个测试数据10分。
*/


#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> s1(n), s2(m), s3(k);
    for (int i = 0; i < n; ++i) {
        std::cin >> s1[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> s2[i];
    }
    for (int i = 0; i < k; ++i) {
        std::cin >> s3[i];
    }

    std::sort(s1.begin(), s1.end());
    std::sort(s2.begin(), s2.end());
    std::sort(s3.begin(), s3.end());

    int i = 0, j = 0, t = 0;
    int result = 9999999;

    while (i < n && j < m && t < k) {
        int a = s1[i], b = s2[j], c = s3[t];
        int min = std::min({a, b, c});
        int max = std::max({a, b, c});

        // 对三个数有 |a-b|+|b-c|+|c-a| = 2 * (max-min)
        int current = 2 * (max - min);
        if (current < result) {
            result = current;
        }

        // 仅移动当前最小值所在指针，才有机会缩小区间 [min, max]
        if (a == min) {
            ++i;
        } else if (b == min) {
            ++j;
        } else {
            ++t;
        }
    }

    std::cout << result << std::endl;
    return 0;
}



