/*
【问题描述】

模拟超市排队的行为。最初，有n个队列（1，2，…，n），每个队列都有一些顾客。之后可能会发生两个事件：

ENTERS：顾客到达队列。如果队列在1到n之间，则顾客到达该队列的末尾。否则，该事件将被忽略；

LEAVES：顾客离开队列。如果队列在1到n之间，并且该队列不为空，则该队列的第一个顾客将离开该队列。否则，该事件将被忽略。

【类库使用要求】可以使用STL类库

【输入形式】

1.     输入从队列的数量n（严格意义上为正的自然数）开始。

2.     按照n行，每个队列一行，每个行按照顾客到达队列的顺序，列出顾客名字。

3.     然后空一行。

4.     事件描述（ENTERS 或者LEAVES）后面，跟着顾客名字和和队列序号（正整数）。

【输出形式】

1.     首先，按离开的顺序打印离开队列的顾客姓名。

2.     然后，按顺序打印n个队列的最终内容。


【样例输入】

5
Lisa Tom
John
Jerry Mary
 
Eric
 
LEAVES 1
LEAVES 2
ENTERS Harry 2
【样例输出】

DEPARTS
Lisa
John
 
FINAL CONTENTS
queue 1: Tom
queue 2: Harry
queue 3: Jerry Mary
queue 4:
queue 5: Eric
*/

#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
	int n;
	std::cin >> n;

	std::string line;
	std::getline(std::cin, line); // Consume the endline after n.

	std::vector<std::deque<std::string>> queues(n + 1);

	for (int i = 1; i <= n; ++i) {
		std::getline(std::cin, line);
		std::istringstream iss(line);
		std::string name;
		while (iss >> name) {
			queues[i].push_back(name);
		}
	}

	std::vector<std::string> departed;

	while (std::getline(std::cin, line)) {
		std::istringstream iss(line);
		std::string eventType;
		if (!(iss >> eventType)) {
			continue;
		}

		if (eventType == "ENTERS") {
			std::string name;
			int index;
			if (iss >> name >> index) {
				if (index >= 1 && index <= n) {
					queues[index].push_back(name);
				}
			}
		} else if (eventType == "LEAVES") {
			int index;
			if (iss >> index) {
				if (index >= 1 && index <= n && !queues[index].empty()) {
					departed.push_back(queues[index].front());
					queues[index].pop_front();
				}
			}
		}
	}

	std::cout << "DEPARTS\n";
	for (const std::string &name : departed) {
		std::cout << name << '\n';
	}

	std::cout << '\n';
	std::cout << "FINAL CONTENTS\n";
	for (int i = 1; i <= n; ++i) {
		std::cout << "queue " << i << ":";
		for (const std::string &name : queues[i]) {
			std::cout << ' ' << name;
		}
		std::cout << '\n';
	}

	return 0;
}
