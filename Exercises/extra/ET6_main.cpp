/*顺序队列基本操作*/
#include <iostream>
#include <string>

int main() {
    int n, m;
    std::cin >> n >> m;
    int* myQueue = new int[n];
    size_t frontIndex = 0; // 队头索引（有元素时指向队头元素）
    size_t rearIndex = 0;  // 队尾索引（有元素时指向队尾元素）
    size_t count = 0;      // 当前元素个数
    for (int i = 0; i < m; ++i) {
        std::string operation;
        std::cin >> operation;
        if (operation == "ENQUEUE") {
            int value;
            std::cin >> value;
            if (count == static_cast<size_t>(n)) {
                std::cout << "FULL\n";
            } else {
                if (count == 0) {
                    frontIndex = rearIndex = 0;
                } else {
                    rearIndex = (rearIndex + 1) % n;
                }
                myQueue[rearIndex] = value;
                ++count;
            }
        } else if (operation == "DEQUEUE") {
            if (count == 0) {
                std::cout << "EMPTY\n";
            } else {
                std::cout << myQueue[frontIndex] << '\n';
                if (count > 1) {    //count==1时出队后队列变空，不需要更新frontIndex
                    frontIndex = (frontIndex + 1) % n;
                }
                --count;
            }
        } else if (operation == "FRONT") {
            if (count == 0) {
                std::cout << "EMPTY\n";
            } else {
                std::cout << myQueue[frontIndex] << '\n';
            }
        } else if (operation == "SIZE") {
            std::cout << count << '\n';
        } else if (operation == "REAR") {
            if (count == 0) {
                std::cout << "EMPTY\n";
            } else {
                std::cout << myQueue[rearIndex] << '\n';
            }
        }
    }

    delete[] myQueue;
}
