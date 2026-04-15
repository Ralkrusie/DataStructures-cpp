/*栈的排序*/
#include <iostream>
#include <stack>

int main() {
    int n;
    std::cin >> n;
    std::stack<int> mainStack;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        mainStack.push(x);
    }
    std::stack<int> helperStack;
    int current;
    while (!mainStack.empty()) {
        current = mainStack.top();
        mainStack.pop();
        while (!helperStack.empty() && helperStack.top() < current) {
            mainStack.push(helperStack.top());
            helperStack.pop();
        }
        helperStack.push(current);
    }
    bool first = true;
    while (!helperStack.empty()) {
        if (!first) {
            std::cout << " ";
        }
        std::cout << helperStack.top();
        helperStack.pop();
        first = false;
    }
}