/*
12. 顺序表基本操作-插入删除查找
一、问题描述
实现一个动态数组（顺序表）的基本操作，包括插入、删除和查找。

给定一个初始为空的顺序表，依次执行m个操作，操作类型如下：

INSERT x：在表尾插入元素x

INSERT k x：在第k个位置插入元素x（1 ≤ k ≤ 当前长度+1）

DELETE k：删除第k个位置的元素（1 ≤ k ≤ 当前长度）

FIND x：查找元素x第一次出现的位置，不存在输出-1

二、输入形式
第一行输入一个正整数m（1 ≤ m ≤ 10000），表示操作数量。
接下来m行，每行一个操作，格式如上所述。
所有元素值为整数（-10⁹ ≤ x ≤ 10⁹）。

三、输出形式
对于每个FIND操作，输出一行一个整数，表示查找结果。

四、样例输入

8
INSERT 5
INSERT 3
INSERT 2 7
FIND 5
FIND 7
DELETE 2
FIND 3
FIND 7
五、样例输出

1
2
-1
2
六、样例说明
操作过程：

INSERT 5：表变为[5]

INSERT 3：表变为[5, 3]

INSERT 2 7：在第2位插入7，表变为[5, 7, 3]

FIND 5：5在第1位，输出1

FIND 7：7在第2位，输出2

DELETE 2：删除第2位，表变为[5, 3]

FIND 3：3现在在第2位，输出2（注意不是原来的位置）

FIND 7：7已不存在，输出-1

七、评分标准
共6个测试用例。

八、类库使用要求
可以使用vector、iostream。禁止使用list、deque等链表结构。
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
	int m;
	std::cin >> m;
	std::string line;
	std::getline(std::cin, line);

	std::vector<int> seq;
	seq.reserve(m);

	for (int i = 0; i < m; ++i) {
		std::getline(std::cin, line);
		if (line.empty()) {
			--i;
			continue;
		}

		std::stringstream ss(line);
		std::string op;
		ss >> op;

		if (op == "INSERT") {
			std::vector<int> args;
			int v;
			while (ss >> v) {
				args.push_back(v);
			}

			if (args.size() == 1) {
				seq.push_back(args[0]);
			} else if (args.size() == 2) {
				int k = args[0];
				int x = args[1];
				seq.insert(seq.begin() + (k - 1), x);
			}
		} else if (op == "DELETE") {
			int k;
			ss >> k;
			seq.erase(seq.begin() + (k - 1));
		} else if (op == "FIND") {
			int x;
			ss >> x;
			int pos = -1;
			for (size_t j = 0; j < seq.size(); ++j) {
				if (seq[j] == x) {
					pos = static_cast<int>(j) + 1;
					break;
				}
			}
			std::cout << pos << '\n';
		}
	}

	return 0;
}

