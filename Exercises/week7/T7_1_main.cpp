/*
【问题描述】

假设一个字符串采用链串表示，设计一个递归算法求t在s中重叠出现的次数。

【输入形式】

第一行输入串s，第二行输入串t。(空格也可以作为串中的一个字符)

【输出形式】

仅一行，输出t在s中重叠出现的次数

【样例输入】

aababad

aba

【样例输出】

2

【样例说明】

aba在aababad重复出现了两次

【评分标准】

题目强调了使用递归算法，仅是普通的遍历会扣分；

题目强调了该串采用链串表示，使用其他形式的会酌情扣分。
*/

#include <iostream>
#include <string>
#include "myString.hpp"

int main() {
	std::string s;
	std::string t;

	std::getline(std::cin, s);
	std::getline(std::cin, t);

	myString text;
	myString pattern;
	text.assign(s.c_str());
	pattern.assign(t.c_str());

	std::cout << text.countOverlapRecursive(pattern) << '\n';
	return 0;
}