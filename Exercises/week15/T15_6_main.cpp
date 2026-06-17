/*
6. 快速排序
【问题描述】

有一个含n（n<=200000）个整数的无序序列，采用快速排序实现递增排序

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

编程语言

*/
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <utility>
using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr) {
    int n = (int)arr.size();
    if (n <= 1) return;
    stack<pair<int, int>> stk;
    stk.push({0, n - 1});
    while (!stk.empty()) {
        int low = stk.top().first;
        int high = stk.top().second;
        stk.pop();
        if (low < high) {
            int pi = partition(arr, low, high);
            if (pi - 1 > low) stk.push({low, pi - 1});
            if (pi + 1 < high) stk.push({pi + 1, high});
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
    quickSort(arr);
    ofstream fout("out.txt");
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) fout << " ";
        fout << arr[i];
    }
    fout << "\n";
    return 0;
}