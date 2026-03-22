#include <iostream>
#include "LinkedStack.hpp"

int main() {
    LinkedStack<int> stack;

    // 测试 push 和 top
    stack.push(10);
    stack.push(20);
    stack.push(30);

    int value;
    if (stack.top(value)) {
        std::cout << "Top element: " << value << std::endl; // 应该输出 30
    }

    // 测试 pop
    while (!stack.isEmpty()) {
        if (stack.pop(value)) {
            std::cout << "Popped element: " << value << std::endl; // 应该依次输出 30, 20, 10
        }
    }

    // 测试 copy constructor
    stack.push(40);
    stack.push(50);
    LinkedStack<int> copiedStack(stack);
    if (copiedStack.top(value)) {
        std::cout << "Top element of copied stack: " << value << std::endl; // 应该输出 50
    }

    // 测试 move constructor
    LinkedStack<int> movedStack(std::move(copiedStack));
    if (movedStack.top(value)) {
        std::cout << "Top element of moved stack: " << value << std::endl; // 应该输出 50
    }
    if (copiedStack.isEmpty()) {
        std::cout << "Copied stack is now empty after move." << std::endl;
    }

    return 0;
}
