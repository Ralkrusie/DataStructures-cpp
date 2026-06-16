/*
【问题描述】

对一个含n（n<=20000）个整数的递增有序表进行折半查找，输出查找成功或失败，并输出每次的查找序列。

【输入形式】

两行字符串，第一行为需要查找的数，第二行包含多个整数，每个数之间用空格分开。

【输出形式】

第一行：查找成功输出”True”，查找失败输出”False”

第二行：输出查找序列，用空格分开

【样例输入一】

1
1 2 3 4 5 6 7 8 9 10

【样例输出一】

True

5 2 1

【样例输入二】

11
1 2 3 4 5 6 7 8 9 10

【样例输出二】

False

5 8 9 10

【样例说明】

测试数据的文件名为in.txt，输出文件名为out.txt

【评分标准】

该题目有10个测试用例，每通过一个测试用例得10分
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ifstream fin("in.txt");
    int target;
    fin >> target;
    vector<int> arr;
    int num;
    while (fin >> num) {
        arr.push_back(num);
    }
    int left = 0;
    int right = arr.size() - 1;
    vector<int> path;
    bool found = false;
    while (left <= right) {
        int mid = (left + right) / 2;
        int compare = arr[mid];
        path.push_back(compare);
        if (compare < target) {
            left = mid + 1;
        } else if (compare > target) {
            right = mid - 1;
        } else {
            found = true;
            break;
        }
    }

    ofstream fout("out.txt");
    fout << (found ? "True\n" : "False\n");
    for (int num : path) {
        fout << num << ' ';
    }
}