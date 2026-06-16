/*
10. 哈夫曼树与哈夫曼编码
哈夫曼树与哈夫曼编码
一、问题描述
给定n个字符及其出现频率，构建哈夫曼树并计算WPL（带权路径长度）。

WPL定义：所有叶子节点的带权路径长度之和，其中带权路径长度 = 权值 × 路径长度（从根到叶子的边数）。

二、输入形式
第一行输入一个正整数n（1 ≤ n ≤ 10000），表示字符数量。
第二行输入n个正整数，表示各字符的出现频率（权值）。

三、输出形式
输出一个整数，表示WPL值。

四、样例输入

4
5 29 7 8
五、样例输出

95
六、样例说明
频率：A=5, B=29, C=7, D=8

哈夫曼树构建过程：

排序：5, 7, 8, 29

合并5+7=12，排序：8, 12, 29

合并8+12=20，排序：20, 29

合并20+29=49

WPL = 5×3 + 7×3 + 8×2 + 29×1 = 15 + 21 + 16 + 29 = 81

（注：不同合并顺序可能产生不同树形，但WPL相同）

七、评分标准
共10个测试用例。

八、类库使用要求
可以使用priority_queue（小顶堆），禁止使用其他容器。


C
(current)


草稿箱
1
​

*/

#include <functional>
#include <iostream>
#include <queue>
#include <vector>

int main() {
	int n;
	std::cin >> n;
	std::priority_queue<long long, std::vector<long long>, std::greater<long long>> minHeap;
	for (int i = 0; i < n; ++i) {
		long long weight;
		std::cin >> weight;
		minHeap.push(weight);
	}
	long long wpl = 0;
	while (minHeap.size() > 1) {
		long long first = minHeap.top();
		minHeap.pop();
		long long second = minHeap.top();
		minHeap.pop();
		long long merged = first + second;
		wpl += merged;
		minHeap.push(merged);
	}
	std::cout << wpl << '\n';
	return 0;
}