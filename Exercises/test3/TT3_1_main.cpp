/*
1. 第五章 主对角线元素求和
【问题描述】设计一个算法，计算 m 行 n 列的二维整数数组 a 的 两条主对角线元素之和。

【输入形式】第一行输入两个整数 m 和 n，分别表示数组 a 的行数和列数。
接下来 m 行，每行 n 个整数，表示二维数组 a 的元素。

【输出形式】

若 m ≠ n，输出 false。

若 m = n，输出 true 和两条主对角线元素之和，格式如下：

true sum

【样例输入】

3 3

1 2 3

4 5 6

7 8 9

【样例输出】

true 30

【样例说明】
【评分标准】

【说明】

可以使用STL库
*/

#include <iostream>

int main() {
    int m, n;
    std::cin >> m >> n;
    if (m != n) {
        std::cout << "false\n";
        return 0;
    }
    std::cout << "true ";

    int sum = 0;
    for (int i = 0; i < m; i++) {
        int a, b;
        a = i;
        b = m - i - 1;
        for (int j = 0; j < m; j++) {
            int num;
            std::cin >> num;
            if (j == a || j == b) {
                sum += num;
                if (a == b) {
                    sum += num;
                }
            }
        }
    }
    std::cout << sum <<std::endl;
}