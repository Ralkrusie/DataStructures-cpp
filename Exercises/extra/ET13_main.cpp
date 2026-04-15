/*
13. 约瑟夫环问题
约瑟夫环问题
一、问题描述
有n个人围成一圈，从第一个人开始报数，数到m的人出列，然后从出列的下一个人重新开始报数，数到m的人再出列，如此反复，直到所有人出列。求出列的顺序。

二、输入形式
一行两个正整数n和m（1 ≤ n ≤ 5000, 1 ≤ m ≤ 10000）。

三、输出形式
输出n个整数，表示出列顺序，用空格分隔。

四、样例输入

5 3
五、样例输出

3 1 5 2 4
六、样例说明
5个人围成一圈：1 2 3 4 5

从1开始报数，1-2-3，3出列

从4开始报数，4-5-1，1出列

从2开始报数，2-4-5，5出列

从2开始报数，2-4-2，2出列

4出列

出列顺序：3 1 5 2 4

七、评分标准
共8个测试用例。

测试用例1-4：小规模数据，模拟法可过

测试用例5-8：较大规模数据，要求O(nm)算法

八、类库使用要求
可以使用iostream、vector、queue。必须手动实现环形链表或使用循环队列。
*/
#include <iostream>
#include <vector>

int main() {
	int n, m;
	std::cin >> n >> m;

	std::vector<int> next(n + 1);
	for (int i = 1; i <= n; ++i) {
		next[i] = (i == n ? 1 : i + 1);
	}

	int prev = n;
	int cur = 1;
	bool first = true;

	for (int remain = n; remain > 0; --remain) {
		for (int cnt = 1; cnt < m; ++cnt) {
			prev = cur;
			cur = next[cur];
		}

		if (!first) {
			std::cout << ' ';
		}
		std::cout << cur;
		first = false;

		next[prev] = next[cur];
		cur = next[cur];
	}
	std::cout << '\n';
	return 0;
}

