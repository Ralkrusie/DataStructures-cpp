/*
【问题描述】

对于给定的正整数 n (
n
>2)，利用一个队列输出 n 阶杨辉三角形（帕斯卡三角形）。
第n阶杨辉三角形的规则如下：

第一行只有一个数字 1；

每行的第一个和最后一个数都是 1；

其余每个数等于上一行相邻两个数之和。

示例：当 
n
=
5 时，杨辉三角形的生成过程如下：

1

1 1

1 2 1

1 3 3 1

1 4 6 4 1

【输入形式】输入一个整数 n（
n
>
2），表示杨辉三角形的阶数。

【输出形式】输出 n 阶杨辉三角形，每行的数字以空格分隔。

【样例输入】5
【样例输出】

1

1 1

1 2 1

1 3 3 1

1 4 6 4 1
*/

#include <iostream>
#include <queue>
#include <vector>

int main() {
	int n;
	std::cin >> n;

	std::queue<long long> currentRow;
	currentRow.push(1);

	for (int rowIndex = 1; rowIndex <= n; ++rowIndex) {
		const int rowSize = static_cast<int>(currentRow.size());
		std::vector<long long> rowValues;
		rowValues.reserve(rowSize);

		for (int i = 0; i < rowSize; ++i) {
			long long value = currentRow.front();
			currentRow.pop();
			rowValues.push_back(value);
			currentRow.push(value);
		}

		for (int i = 0; i < rowSize; ++i) {
			if (i > 0) {
				std::cout << ' ';
			}
			std::cout << rowValues[i];
		}
		std::cout << '\n';

		std::queue<long long> nextRow;
		nextRow.push(1);
		for (int i = 1; i < rowSize; ++i) {
			nextRow.push(rowValues[i - 1] + rowValues[i]);
		}
		nextRow.push(1);
		currentRow = std::move(nextRow);
	}

	return 0;
}