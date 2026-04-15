/*
14. 判断链表是否有环
判断链表是否有环
一、问题描述
给定一个单链表，判断链表中是否存在环。如果存在环，输出"YES"；否则输出"NO"。

链表节点值为整数，输入格式特殊：每行输入两个整数val和next，val表示节点值，next表示下一个节点的位置索引（-1表示NULL）。

二、输入形式
第一行输入一个正整数n（1 ≤ n ≤ 100000），表示节点数量。
接下来n行，每行两个整数val和next，表示第i个节点的值和下一个节点的索引（1-indexed）。

三、输出形式
输出"YES"或"NO"，表示链表是否有环。

四、样例输入

4
1 2
2 3
3 4
4 2
五、样例输出

YES
六、样例说明
链表结构：1 → 2 → 3 → 4 → 2（形成环：2→3→4→2）

七、评分标准
共6个测试用例。

测试用例1-3：小规模数据，哈希法可过

测试用例4-6：大规模数据，要求使用快慢指针法（Floyd判圈算法）

八、类库使用要求
可以使用iostream、vector。要求使用Floyd判圈算法，空间复杂度O(1)。
*/
#include <iostream>
#include <vector>

int main() {
	int n;
	std::cin >> n;

	std::vector<int> nxt(n + 1, -1);
	for (int i = 1; i <= n; ++i) {
		int val, ne;
		// 忽略val，因为题目只关心链表结构
		std::cin >> val >> ne;
		nxt[i] = ne;
	}

	int slow = 1;
	int fast = 1;

	while (fast != -1 && nxt[fast] != -1) {
		slow = nxt[slow];
		fast = nxt[nxt[fast]];
		if (slow == fast) {
			std::cout << "YES\n";
			return 0;
		}
	}

	std::cout << "NO\n";
	return 0;
}

