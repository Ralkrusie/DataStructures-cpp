/*
【问题描述】一个任务处理系统按照到达时间的顺序依次处理任务（注意：不一定是输入次序），但相同到达时间的不同任务的处理顺序与输入顺序一致。每个任务有两个属性：到达时间和执行时间（分别以arrival和execution表示）。当系统空闲时，如果有任务到达，立即处理；否则，任务进入等待队列。当一个任务开始处理时，其等待时间为开始时间减去到达时间。请计算所有任务的总等待时间。

【输入形式】输入的第一行是一个整数N（1 <= N <= 50），表示有N个任务。接下来N行，每行包含两个整数：arrival和execution，分别表示每个任务的到达时间和执行时间，其中0 <= arrival, execution <= 100。

【输出形式】输出一个整数，即所有任务总等待时间。

【样例输入】

3
0 5
2 4
7 2

【样例输出】

5

【样例说明】第一个任务无需等待即可开始处理，因此其等待时间为0。第二个任务在第一个任务执行完后（第5秒）才执行，因此其等待时间为5-2=3秒。第三个任务在第二个任务完成（第9秒）后开始，等待9-7=2秒。总等待时间=0+3+2=5。

【评分标准】允许使用STL。
*/

#include <iostream>
#include <algorithm>
#include <vector>

struct Task {
	int arrival;
	int execution;
};

int main() {
	int n;
	std::cin >> n;

	std::vector<Task> tasks(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> tasks[i].arrival >> tasks[i].execution;
	}

	// Stable sort keeps input order for tasks with equal arrival time.
	std::stable_sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
		return a.arrival < b.arrival;
	});

	int currentTime = 0;
	int totalWait = 0;

	for (const Task &task : tasks) {
		if (currentTime < task.arrival) {
			currentTime = task.arrival;
		}

		totalWait += currentTime - task.arrival;
		currentTime += task.execution;
	}

	std::cout << totalWait << '\n';
	return 0;
}
