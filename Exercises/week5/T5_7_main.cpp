/*
题目描述
zky 有 n 个扑克牌，编号从 1 到 n，zky 把它排成一个序列，每次把最上方的扑克牌放在牌堆底，然后把下一张扑克牌拿出来输出，最终输出的序列恰好是从 1 到 n，faebdc 问你原序列是什么，因为 faebdc 神犇早已在 O(1) 的时间得出结果，如果你在 1 s 内答不出来，faebdc 会吃了你。

输入格式
一个整数 n，表示扑克数目。

输出格式
n 个数，表示扑克序列。

输入输出样例
输入 #1

13
输出 #1

7 1 12 2 8 3 11 4 9 5 13 6 10


*/

#include <deque>
#include <iostream>

int main() {
	int n;
	std::cin >> n;

	std::deque<int> cards;

	// Reverse process: from output n..1 reconstruct original top-to-bottom order.
	for (int value = n; value >= 1; --value) {
		cards.push_front(value);
		if (cards.size() > 1) {
			int last = cards.back();
			cards.pop_back();
			cards.push_front(last);
		}
	}

	for (int i = 0; i < n; ++i) {
		if (i > 0) {
			std::cout << ' ';
		}
		std::cout << cards[i];
	}
	std::cout << '\n';

	return 0;
}
