/*用栈实现队列*/
#include <iostream>
#include <stack>
int main(){
    int m;
    std::cin >> m;
    std::stack<int> stackIn, stackOut;
    for (int i = 0; i < m; ++i) {
        std::string operation;
        std::cin >> operation;
        if (operation == "ENQUEUE") {
            int value;
            std::cin >> value;
            stackIn.push(value);
        } else if (operation == "DEQUEUE") {
            if (stackOut.empty()) {
                while (!stackIn.empty()) {
                    stackOut.push(stackIn.top());
                    stackIn.pop();
                }
            }
            if (!stackOut.empty()) {
                std::cout << stackOut.top() << '\n';
                stackOut.pop();
            } else {
                std::cout << "EMPTY\n";
            }
        } else if (operation == "PEEK") {
            if (stackOut.empty()) {
                while (!stackIn.empty()) {
                    stackOut.push(stackIn.top());
                    stackIn.pop();
                }
            }
            if (!stackOut.empty()) {
                std::cout << stackOut.top() << '\n';
            } else {
                std::cout << "EMPTY\n";
            }
        }
    }
}