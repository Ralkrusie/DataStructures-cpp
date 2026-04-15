/*
中缀转后缀表达式
一、问题描述
给定一个中缀表达式，将其转换为后缀表达式（逆波兰表达式）。

表达式只包含非负整数、+、-、*、/、括号。

注意：

运算符优先级：*和/高于+和-

同级运算符从左到右计算

括号可以改变优先级

二、输入形式
一行一个字符串，表示中缀表达式，无空格，数字可能有多位。

三、输出形式
输出后缀表达式，数字和运算符之间用空格分隔。

四、样例输入

3+4*2/(1-5)
五、样例输出

3 4 2 * 1 5 - / +
六、样例说明
中缀表达式"3+4*2/(1-5)"的转换过程：

3直接输出

+入栈

4直接输出

优先级高于栈顶+，入栈

2直接输出

/优先级等于栈顶，出栈输出，/入栈

(入栈

1直接输出

-入栈（栈顶是(，直接入栈）

5直接输出

)出栈直到(，-出栈输出，(出栈丢弃

表达式结束，栈中/和+依次出栈输出

结果：3 4 2 * 1 5 - / +

七、评分标准
共8个测试用例。

八、类库使用要求
可以使用栈，可以使用string、vector。
*/
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>   // for isdigit

int main() {
    std::string infix;
    std::cin >> infix;

    std::stack<std::string> operators;
    std::vector<std::string> output;

    // 定义运算符优先级的lambda函数
    auto precedence = [](const std::string& op) {
        if (op == "+" || op == "-") return 1;
        if (op == "*" || op == "/") return 2;
        if (op == "**") return 3;
        return 0;
    };

    auto isRightAssociative = [](const std::string& op) {
        return op == "**";
    };

    for (size_t i = 0; i < infix.size();) {
        if (isdigit(infix[i])) {    // 处理多位数字
            size_t j = i;
            while (j < infix.size() && isdigit(infix[j])) {
                ++j;
            }
            output.push_back(infix.substr(i, j - i));
            i = j;
        } else if (infix[i] == '(') {
            operators.push("(");   // '('直接入栈
            ++i;
        } else if (infix[i] == ')') {   // ')'出栈直到遇到'('
            while (!operators.empty() && operators.top() != "(") {
                output.push_back(operators.top());
                operators.pop();    // 出栈运算符
            }
            if (!operators.empty()) {
                operators.pop(); // pop '('
            }
            ++i;
        } else { // operator
            std::string currentOp;
            if (infix[i] == '*' && i + 1 < infix.size() && infix[i + 1] == '*') {
                currentOp = "**";
                i += 2;
            } else {
                currentOp = std::string(1, infix[i]);
                ++i;
            }

            while (!operators.empty() && operators.top() != "(") {
                const std::string topOp = operators.top();
                const bool shouldPop = (!isRightAssociative(currentOp) && precedence(topOp) >= precedence(currentOp)) ||
                                       (isRightAssociative(currentOp) && precedence(topOp) > precedence(currentOp));
                if (!shouldPop) {
                    break;
                }
                output.push_back(topOp);
                operators.pop();
            }
            operators.push(currentOp);
        }
    }

    while (!operators.empty()) {
        output.push_back(std::string(operators.top()));
        operators.pop();
    }

    for (size_t i = 0; i < output.size(); ++i) {
        std::cout << output[i];
        if (i < output.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;

    return 0;
}