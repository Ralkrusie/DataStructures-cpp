/*中缀转后缀表达式*/
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>

auto priority = [](char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return -1; // 非运算符
};

int main() {
    char ch;
    std::vector<char> output;
    std::stack<char> operators;
    while (std::cin >> ch) {
        if (isdigit(ch)) {
            output.push_back(ch);
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                output.push_back(operators.top());
                operators.pop();
            }
            if (!operators.empty()) {
                operators.pop(); // pop '('
            }
        } else { // operators
            while (!operators.empty() && priority(ch) <= priority(operators.top())) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(ch);
        }
    }
    while (!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }
    for (const char &c : output) {
        std::cout << c << ' ';
    }
}