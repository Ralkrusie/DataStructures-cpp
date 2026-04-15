/*顺序栈基本操作*/
#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> myStack;
    //size_t topIndex = 0; // 栈顶索引，初始为0表示栈空

    for (int i = 0; i < m; ++i) {
        std::string operation;
        std::cin >> operation;
        if (operation == "PUSH") {
            int value;
            std::cin >> value;
            if (myStack.size() < static_cast<size_t>(n)) {
                myStack.push_back(value);
            } else {
                std::cout << "FULL\n";
            }

        } else if (operation == "POP") {
            if (!myStack.empty()) {
                std::cout << myStack.back() << '\n';
                myStack.pop_back();
            } else {
                std::cout << "EMPTY\n";
            }
        } else if (operation == "TOP") {
            if (!myStack.empty()) {
                std::cout << myStack.back() << '\n';
            } else {
                std::cout << "EMPTY\n";
            }
        } else if (operation == "SIZE") {
            std::cout << myStack.size() << '\n';
        }
    }
}