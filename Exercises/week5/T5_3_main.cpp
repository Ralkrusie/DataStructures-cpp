/*
【问题描述】

  设计一个循环队列（Circular Queue）来模拟数据缓冲区（假定缓冲区中的数据都是整数）的管理。循环队列的容量固定为 k(0=<k<=100)，支持以下操作：

  enqueue(value)：向队列尾部插入一个元素。如果队列已满，则丢弃最早入队的元素（即覆盖最旧的数据），再插入新元素。

  dequeue()：移除并返回队列头部的元素。如果队列为空，返回 -1。

  get_oldest()：返回最早入队的元素（不移除）。如果队列为空，返回 -1。

  get_latest()：返回最近入队的元素（不移除）。如果队列为空，返回 -1。

要求：

  所有操作的时间复杂度必须为 O(1)。不能使用STL的队列容器，必须手动实现循环队列(不一定按照教材，可自行定义，注意分配的空间都用来存放数据，不需要空一个）。

提示：请正确处理循环队列的所有边界情况，包括队列空、队列满、覆盖写入等情况。


【输入形式】

  第一行：k（队列容量）和 m（操作数量）。

  接下来 m 行，每行一个操作：

   enqueue x（插入元素 x） 

   dequeue（移除并返回头部元素）

   get_oldest（查询最早元素）

   get_latest（查询最新元素）


【输出形式】

   对于 dequeue、get_oldest、get_latest 操作，输出对应的返回值。



【样例输入】

3 8

enqueue 1

enqueue 2

enqueue 3

enqueue 4

get_oldest

dequeue

get_latest

dequeue


【样例输出】

2

2

4

3

【样例说明】

enqueue 1 → [1]

enqueue 2 → [1, 2]

enqueue 3 → [1, 2, 3]（队列满）

enqueue 4 → [2, 3, 4]（覆盖最旧的 1）

get_oldest → 最早的是 2

dequeue → 移除 2，返回 2

get_latest → 最新的是 4

dequeue → 移除 3，返回 3 


【评分标准】不允许使用STL中的队列容器，可以使用vector，一共5个测试用例，通过一个得6分，是标准的输入输出。
*/

#include <iostream>
#include <string>

class myCircularQueue {
public:
    explicit myCircularQueue(const int &k): buffer(nullptr), capacity(k), head(0), size(0) {
        if (capacity > 0) {
            buffer = new int[capacity];
        }
    };

    ~myCircularQueue() {
        delete[] buffer;
    };

    void enqueue(const int &value) {
        if (capacity <= 0) {
            return;
        }

        const int tail = (head + size) % capacity;
        buffer[tail] = value;

        if (size == capacity) {
            head = (head + 1) % capacity;
        } else {
            ++size;
        }
    };

    int dequeue() {
        if (isEmpty()) {
            return -1;
        }

        const int value = buffer[head];
        head = (head + 1) % capacity;
        --size;
        return value;
    };

    int getOldest() const {
        if (isEmpty()) {
            return -1;
        }
        return buffer[head];
    };

    int getLatest() const {
        if (isEmpty()) {
            return -1;
        }
        const int latestIndex = (head + size - 1) % capacity;
        return buffer[latestIndex];
    };

    bool isEmpty() const {
        return size == 0;
    };

private:
    int *buffer;
    int capacity;
    int head;
    int size;
};

int main() {
  int k, m;
  std::cin >> k >> m;

  myCircularQueue queue(k);
  std::string op;

  for (int i = 0; i < m; ++i) {
    std::cin >> op;
    if (op == "enqueue") {
      int x;
      std::cin >> x;
      queue.enqueue(x);
    } else if (op == "dequeue") {
      std::cout << queue.dequeue() << '\n';
    } else if (op == "get_oldest") {
      std::cout << queue.getOldest() << '\n';
    } else if (op == "get_latest") {
      std::cout << queue.getLatest() << '\n';
    }
  }

  return 0;
}
