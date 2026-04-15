/*
2. LeetCode28—实现strStr()
【问题描述】


给定一个s字符串和一个t字符串，在s字符串中找出t字符串出现的第一个位置（从0开始），如果不存在则返回-1。例如，输入s="hello"，t="ll"，输出结果为2。设计如下成员函数：




class Solution {
public:
 int strStr(string s, string t)
 {  …  }
};


【输入形式】

     输入两个字符串，先输入的为s串，后输入的为t串。字符串中允许出现空格符。


【输出形式】

     t串在s串中出现的第一个位置。若t串不在s串中，则返回-1。


【样例输入】

    hello

    ll


【样例输出】

    2


【样例说明】

      s串为“hello”，t串为“ll”，t串在s串中第一次出现的位置为2（从0开始计数）。测试数据存放在in.txt文件中。
*/

#include <iostream> 
#include <string>
#include <fstream>
#include <cstddef>
#include <algorithm>


int main() {
    std::ifstream fin("in.txt");
    std::string s, t;
    std::getline(fin, s);
    std::getline(fin, t);

    size_t pos = s.find(t);
    if (pos != std::string::npos) {
        std::cout << pos << std::endl;
    } else {
        std::cout << -1 << std::endl;
    }

    return 0;
}