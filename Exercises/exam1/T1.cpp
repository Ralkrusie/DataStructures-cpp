/*
请编程实现一个队列（Queue）数据结构，并完成指定的队列操作。要求自行实现队列的存储结构，不允许使用任何现成的队列库函数或容器，如使用STL容器扣50%得分。

你需要实现以下基本操作：

入队（IN）：将元素添加到队尾

出队（OUT）：将队头元素移除

获取队头（GET）：查看当前队头元素

获取大小（SIZE）：查看队列中有效元素个数

输入形式
第一行：一个整数 maxSize（2 ≤ maxSize ≤ 1000），表示队列最大可存储元素数量

第二行：一个整数 k（1 ≤ k ≤ 1000），表示操作次数

接下来 k 行：每行一条操作指令，格式如下：

指令	说明
IN x	将整数 x 入队；若队列已满，则不执行
OUT	队头元素出队；若队列为空，则不执行
GET	输出当前队头元素；若队列为空，输出 -1
SIZE	输出当前队列中有效元素个数
输出形式
对于每条 GET、SIZE 指令，单独输出一行结果。

样例输入
5
10
IN 10
IN 20
IN 30
GET
SIZE
OUT
GET
IN 40
IN 50
SIZE
样例输出
10
3
20
4
样例说明
队列容量为 5，执行 10 条操作指令

IN 10、IN 20、IN 30：依次将 10、20、30 入队，队列变为 [10, 20, 30]（3个元素）

GET：输出队头元素 10

SIZE：输出队列中有效元素个数 3

OUT：队头元素 10 出队，队列变为 [20, 30]（2个元素）

GET：输出当前队头元素 20

IN 40、IN 50：继续入队，队列变为 [20, 30, 40, 50]（4个元素）

SIZE：输出队列中有效元素个数 4
*/
#include <cstddef>
#include <iostream>


class myQueue {
public:
	myQueue() : headNode(nullptr), tailNode(nullptr), size(0) {}

	~myQueue() {
		clear();
	}

	void push(const int &x) {
		Node *newNode = new Node(x);
		if (tailNode == nullptr) {
			headNode = tailNode = newNode;
		} else {
			tailNode->next = newNode;
			tailNode = newNode;
		}
		++size;
	}

	void pop() {
		if (isEmpty()) {
			return;
		}
		Node *oldHead = headNode;
		headNode = headNode->next;
		delete oldHead;
		--size;
		if (headNode == nullptr) {
			tailNode = nullptr;
		}
	}

	int front() const {
		if (isEmpty()) {
			return -1;
		}
		return headNode->value;
	}

	bool isEmpty() const {
		return size == 0;
	}

	size_t getSize() const {
		return size;
	}

	void clear() {
		while (headNode != nullptr) {
			Node *current = headNode->next;
			delete headNode;
			headNode = current;
		}
		tailNode = nullptr;
		size = 0;
	}


private:
	struct Node {
		int value;
		Node *next;
		Node(const int &x) : value(x), next(nullptr) {}
	};

	Node *headNode;
	Node *tailNode;
	size_t size;
};

int main() {
    size_t maxSize;
    std::cin >> maxSize;
    int k;
    std::cin >> k;
    myQueue que;
    for (int i = 0; i < k; i++) {
        std::string operation;
        std::cin >> operation;
        if (operation == "IN") {
            int x;
            std::cin >> x;
            if (que.getSize() >= maxSize) {
                continue;
            }
            que.push(x);
        } else if (operation == "OUT") {
            que.pop();
        } else if (operation == "GET") {
            std::cout << que.front() << std::endl;
        } else if (operation == "SIZE") {
            std::cout << que.getSize() << std::endl;
        }
    }
}
