/*
栈的排序
一、问题描述
给定一个栈，将其中的元素按从栈顶到栈底递增的顺序排序。只能使用一个额外的辅助栈，不能使用其他数据结构。

输入为先入栈的元素（栈底到栈顶），输出要求栈顶到栈底递增。

二、输入形式
第一行输入一个正整数n（1 ≤ n ≤ 10000），表示栈中元素个数。
第二行输入n个整数，表示栈中元素（从栈底到栈顶）。

三、输出形式
输出排序后的栈中元素（从栈顶到栈底），用空格分隔。

四、样例输入

5
3 1 4 2 5
五、样例输出

1 2 3 4 5
六、样例说明
原栈（栈底到栈顶）：3 1 4 2 5
要求排序后（栈顶到栈底递增）：1 2 3 4 5

排序过程：

使用辅助栈，将原栈元素按递减顺序放入辅助栈

将辅助栈元素倒回原栈，即为递增顺序

七、评分标准
共8个测试用例。

八、类库使用要求
只能使用两个栈，禁止使用数组、优先队列等其他数据结构。
*/
#include <iostream>
#include <stack>

int main() {
	int n;
	std::cin >> n;

	std::stack<int> s;
	std::stack<int> helper;

	// 输入顺序是栈底到栈顶，按输入顺序依次入栈即可。
	for (int i = 0; i < n; ++i) {
		int x;
		std::cin >> x;
		s.push(x);
	}

	// 维护helper从栈顶到栈底递减，最终倒回s后即得到从栈顶到栈底递增。
    // 需要一个变量cur来保存当前s栈顶元素，比较helper栈顶元素与cur的大小关系。
	while (!s.empty()) {
		int cur = s.top();
		s.pop();

		while (!helper.empty() && helper.top() < cur) {
			s.push(helper.top());
			helper.pop();
		}
		helper.push(cur);
	}

	// while (!helper.empty()) {
	// 	s.push(helper.top());
	// 	helper.pop();
	// }

	// bool first = true;
	// while (!s.empty()) {
	// 	if (!first) {
	// 		std::cout << " ";
	// 	}
	// 	std::cout << s.top();
	// 	s.pop();
	// 	first = false;
	// }
	// std::cout << '\n';
    bool first = true;
    while (!helper.empty()) {
        if (!first) {
            std::cout << " ";
        }
        std::cout << helper.top();
        helper.pop();
        first = false;
    }

	return 0;
}