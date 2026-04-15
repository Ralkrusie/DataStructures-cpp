/*
题目描述
给定一个数列，初始为空，请支持下面三种操作：

给定一个整数 
x
x，请将 
x
x 加入到数列中。

输出数列中最小的数。

删除数列中最小的数（如果有多个数最小，只删除 
1
1 个）。

输入格式
第一行是一个整数，表示操作的次数 
n
n。
接下来 
n
n 行，每行表示一次操作。每行首先有一个整数 
o
p
op 表示操作类型。

若 
o
p
=
1
op=1，则后面有一个整数 
x
x，表示要将 
x
x 加入数列。

若 
o
p
=
2
op=2，则表示要求输出数列中的最小数。

若 
o
p
=
3
op=3，则表示删除数列中的最小数。如果有多个数最小，只删除 
1
1 个。

输出格式
对于每个操作 
2
2，输出一行一个整数表示答案。

输入输出样例 #1
输入 #1
5
1 2
1 5
2
3
2
输出 #1
2
5
*/

#include <iostream>
#include <queue>
#include <vector>

int main() {
	int n;
	std::cin >> n;

	std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

	for (int i = 0; i < n; ++i) {
		int op;
		std::cin >> op;

		if (op == 1) {
			int x;
			std::cin >> x;
			minHeap.push(x);
		} else if (op == 2) {
			if (!minHeap.empty()) {
				std::cout << minHeap.top() << '\n';
			}
		} else if (op == 3) {
			if (!minHeap.empty()) {
				minHeap.pop();
			}
		}
	}

	return 0;
}