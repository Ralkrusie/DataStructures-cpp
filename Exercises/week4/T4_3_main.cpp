/*后缀表达式求值*/
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <sstream>

int main() {
    std::string str;
    std::stack<int> numbers;
    int result = 0;
    int left, right;
    std::string input;
    std::getline(std::cin, input);
    std::istringstream ss(input);
    while (ss >> str) {
        if (isdigit(str[0])) {
            numbers.push(std::stoi(str));   //stoi将字符串转换为整数
        } else {
            right = numbers.top();
            numbers.pop();
            left = numbers.top();
            numbers.pop();
            switch (str[0]) {
                case '+':
                    result = left + right;
                    break;
                case '-':
                    result = left - right;
                    break;
                case '*':
                    result = left * right;
                    break;
                case '/':
                    result = left / right;
                    break;
                default:
                    return 1;
            }
            numbers.push(result);
        }
    }
    std::cout << numbers.top() << std::endl;
    return 0;
}