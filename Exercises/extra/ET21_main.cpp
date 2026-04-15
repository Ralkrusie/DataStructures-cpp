/*
21. 有序顺序表合并
有序顺序表合并
一、问题描述
给定两个已经按非递减顺序排列的整数数组，将它们合并成一个新的有序数组，要求结果数组也是非递减顺序。

二、输入形式
第一行输入两个正整数n和m（1 ≤ n, m ≤ 100000），分别表示两个数组的长度。
第二行输入n个整数，表示第一个有序数组。
第三行输入m个整数，表示第二个有序数组。

三、输出形式
输出合并后的有序数组，共n+m个整数，用空格分隔。

四、样例输入

4 5
1 3 5 7
2 3 4 6 8
五、样例输出

1 2 3 3 4 5 6 7 8
六、样例说明
两个有序数组合并：

使用双指针法，比较两个数组当前元素，取较小者放入结果

当一个数组遍历完后，将另一个数组剩余元素全部放入结果

七、评分标准
共6个测试用例。

测试用例1-2：小规模数据

测试用例3-6：大规模数据，要求O(n+m)算法

八、类库使用要求
可以使用vector、iostream。禁止使用merge、sort等STL算法。
*/
#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }

    std::vector<int> c;
    c.reserve(n + m);

    int i = 0;
    int j = 0;
    while (i < n && j < m) {
        if (a[i] <= b[j]) {
            c.push_back(a[i++]);
        } else {
            c.push_back(b[j++]);
        }
    }
    while (i < n) {
        c.push_back(a[i++]);
    }
    while (j < m) {
        c.push_back(b[j++]);
    }

    for (size_t k = 0; k < c.size(); ++k) {
        if (k > 0) {
            std::cout << ' ';
        }
        std::cout << c[k];
    }
    std::cout << '\n';
    return 0;
}