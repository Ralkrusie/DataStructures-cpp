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
#include <map>

int main(){
    // 当前实现复杂度：
    // 1) 读入并建立映射：O(n log n)（map 插入）
    // 2) 三重循环判定：O(n^3)
    // 总时间复杂度 O(n^3)，空间复杂度 O(n)
    size_t n;

    std::cin >> n;
    std::map<char, size_t> inOrder;
    std::vector<char> toJudge(n);

    for (size_t i = 0; i < n; i++){
        char ch;
        std::cin >> ch;
        inOrder[ch] = i;
    }
    for (size_t i = 0; i < n; i++){
        std::cin >> toJudge[i];
    }
    for (size_t i = 0; i < n - 2; i++){
        for (size_t j = i + 1; j < n - 1; j++){
            for (size_t k = j + 1; k < n; k++){
                if (inOrder[toJudge[j]] < inOrder[toJudge[k]] && inOrder[toJudge[k]] < inOrder[toJudge[i]]){
                    std::cout << "false";
                    return 0;
                }
            }
        }
    }
    std::cout << "true";
    return 0;
}

