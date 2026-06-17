/*
1. 哈希查找
【问题描述】

对一个含n（n<=200）个正整数的无序序列构建一个长为200的哈希表，其哈希函数为h（key）=key%199，采用线性探测法解决冲突，输出查找成功或失败，并输出每次的查找序列。

【输入形式】

两行字符串，第一行为需要查找的数，第二行为无序正整数序列，每个数之间用空格分开。

【输出形式】

第一行：查找成功输出"True"，查找失败输出"False"

第二行：输出查找序列，每个数之间用空格分开

【样例输入一】

1

1 2 3 4 5 6 7 8 9 10

【样例输出一】

True

1

【样例输入二】

200

1 2 3 4 5 6 7 8 9 10

【样例输出二】

False

1 2 3 4 5 6 7 8 9 10

【样例说明】

测试数据的文件名为in.txt，输出文件名为out.txt

【评分标准】

该题目有10个测试用例，每通过一个测试用例得10分
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

const int TABLE_SIZE = 200;

int main() {
    ifstream fin("in.txt");
    int target;
    fin >> target;
    vector<int> hashTable(TABLE_SIZE, -1);
    vector<bool> used(TABLE_SIZE, false);
    int num;
    // 构建哈希表
    while (fin >> num) {
        int idx = num % 199;
        while (used[idx]) {
            idx = (idx + 1) % TABLE_SIZE;
        }
        hashTable[idx] = num;
        used[idx] = true;
    }

    // 查找
    vector<int> path;
    bool found = false;
    int idx = target % 199;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        int cur = (idx + i) % TABLE_SIZE;
        if (!used[cur]) {
            // 遇到空位，查找失败
            break;
        }
        path.push_back(hashTable[cur]);
        if (hashTable[cur] == target) {
            found = true;
            break;
        }
    }

    ofstream fout("out.txt");
    fout << (found ? "True\n" : "False\n");
    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) fout << " ";
        fout << path[i];
    }
    fout << "\n";
    return 0;
}