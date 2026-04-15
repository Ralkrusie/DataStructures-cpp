/*括号匹配*/
#include <iostream>
#include <string>
#include <stack>

int main() {
    std::string str;
    std::stack<int> parentheses;
    std::cin >> str;
    for (const char &ch : str) {
        switch(ch) {
            case ')':
                if (parentheses.empty() || parentheses.top() != '(') {
                    std::cout << "NO\n";
                    return 0;
                } else {
                    parentheses.pop();
                }
                break;
            case ']':
                if (parentheses.empty() || parentheses.top() != '[') {
                    std::cout << "NO\n";
                    return 0;
                } else {
                    parentheses.pop();
                }
                break;
            case '}':
                if (parentheses.empty() || parentheses.top() != '{') {
                    std::cout << "NO\n";
                    return 0;
                } else {
                    parentheses.pop();
                }
                break;
            default:
                parentheses.push(ch);
                break;
        }
    }
    if (parentheses.empty()) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}