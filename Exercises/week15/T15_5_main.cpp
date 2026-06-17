/*
5. 希尔排序
【问题描述】

有一个含n（n<=200000）个整数的无序序列，采用希尔排序实现递增排序

【输入形式】

一行字符串，包含多个整数，每个数之间用空格分开。

【输出形式】

递增排序的结果，每个数之间用空格分开。

【样例输入】

9 4 7 6 2 5 8 1 3

【样例输出】

1 2 3 4 5 6 7 8 9

【样例说明】

测试数据的文件名为in.txt，输出文件名为out.txt

【评分标准】

该题目有10个测试用例，每通过一个测试用例得10分
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void shellSort(vector<int>& arr) {
    int n = (int)arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

int main() {
    ifstream fin("in.txt");
    vector<int> arr;
    int num;
    while (fin >> num) {
        arr.push_back(num);
    }
    shellSort(arr);
    ofstream fout("out.txt");
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) fout << " ";
        fout << arr[i];
    }
    fout << "\n";
    return 0;
}