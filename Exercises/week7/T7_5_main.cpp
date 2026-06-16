/*
5. 十进制数转任意进制
【问题描述】

将正整数m（十进制）利用n进制表示，n是正整数且n>=2，得到的n进制数每一位依次存储在一个数组num中，num[0]为最高位。说明：n进制的每一位用数字i表示，i可以>=10。

【输入形式】

m n
【输出形式】

n进制表示的每一位（从高位到低位，每一位中间用空格隔开，最高位不能为0）
【样例输入】

11 2
【样例输出】

1 0 1 1
【样例说明】

输入文件名字为in.txt

输出文件名字为out.txt
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

int main() {
    std::ifstream fin("in.txt");
    std::ofstream fout("out.txt");

    int m, n;
    fin >> m >> n;

    std::vector<int> num;
    while (m > 0) {
        num.push_back(m % n);
        m /= n;
    }
    std::reverse(num.begin(), num.end());

    for (size_t i = 0; i < num.size(); ++i) {
        fout << num[i];
        if (i + 1 < num.size()) {
            fout << ' ';
        }
    }
    fout << '\n';

    return 0;
}