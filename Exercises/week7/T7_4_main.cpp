/*
【问题描述】

对于字符串 s，设计一个算法在 s 中查找字符 c 最后一次出现的位置 (下标从0开始计数)，找到后输出其位置，如果没有找到请输出 -1。



【输入形式】

第一行为一个字符串 s

第二行为一个字符 c

保证 s 只由 a~z 以及空格构成，c 只会是小写字母



【输出形式】

输出为一个整数，表示字符 c 在字符串 s 中最后一次出现的位置，如果未找到则输出 -1。



【样例输入1】

hello world
o
【样例输出1】

7
【样例输入2】

hello world
z
【样例输出2】

-1
*/

#include <iostream>
#include <string>

int main() {
    std::string s;
    std::getline(std::cin, s);
    char c;
    std::cin >> c;

    int result = -1;
    for (size_t i = s.size() - 1; i >= 0; --i) {
        if (s[i] == c) {
            result = static_cast<int>(i);
            break;
        }
    }
    std::cout << result << '\n';
    return 0;
}