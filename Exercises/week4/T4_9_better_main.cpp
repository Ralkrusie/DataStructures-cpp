/*
【问题描述】

现有一个以英文字母组成的字符序列，序列的元素个数为N（3<N<26），该序列通过一个顺序栈可以得到多种出栈序列，设计一个算法判断输入的序列str是否为一个合适的出栈序列。
【输入形式】

第一行输入序列的元素个数N（3<N<26）

第二行按顺序输入该序列的所有元素，输入顺序即为进栈的顺序

第三行输入一个不知道是否正确的出栈序列
【输出形式】

判断第三行输入的是否为可能的出栈序列，如果是则输出true，如果不是则输出false。
【样例输入】

5

a b c d e

a b c d e
【样例输出】

true
【样例说明】

字符之间有空格
*/

#include <iostream>
#include <stack>
#include <vector>
#include <cstddef>

int main() {
    // 顺序栈模拟法复杂度：
    // 1) 每个元素最多入栈一次、出栈一次
    // 总时间复杂度 O(n)，空间复杂度 O(n)
    size_t n;
    std::cin >> n;

    std::vector<char> inSeq(n), outSeq(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> inSeq[i];
    }
    for (size_t i = 0; i < n; i++) {
        std::cin >> outSeq[i];
    }

    std::stack<char> st;
    size_t i = 0;
    size_t j = 0;

    while (j < n) {
        if (!st.empty() && st.top() == outSeq[j]) {
            st.pop();
            j++;
        } else if (i < n) {
            st.push(inSeq[i]);
            i++;
        } else {
            std::cout << "false";
            return 0;
        }
    }

    std::cout << "true";
    return 0;
}
