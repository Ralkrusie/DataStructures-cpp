/*用队列实现栈*/
#include <iostream>
#include <queue>
int main(){
    int m;
    std::cin >> m;
    std::queue<int> q1, q2;
    for (int i = 0; i < m; ++i) {
        std::string operation;
        std::cin >> operation;
        if (operation == "PUSH"){
            int value;
            std::cin >> value;
            q1.push(value);
        } else if (operation == "POP") {
            if (q1.empty()) {
                std::cout << "EMPTY\n";
            } else {
                while (q1.size() > 1) {
                    q2.push(q1.front());
                    q1.pop();
                }
                std::cout << q1.front() << '\n';
                q1.pop();
                std::swap(q1, q2);
            }
        } else if (operation == "TOP") {
            if (q1.empty()) {
                std::cout << "EMPTY\n";
            } else {
                while (q1.size() > 1) {
                    q2.push(q1.front());
                    q1.pop();
                }
                std::cout << q1.front() << '\n';
                q2.push(q1.front());
                q1.pop();
                std::swap(q1, q2);
            }
        }
    }
    return 0;
}