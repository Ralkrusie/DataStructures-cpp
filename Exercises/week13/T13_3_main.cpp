/*
3. 第九章第3题
【问题描述】
设计一个折半查找算法，用于在一个有序数组中查找关键字为 k 的元素，并统计成功查找到该元素过程中关键字的比较次数。在查找过程中，每一次执行 R[mid] == k 或者 k < R[mid] （或者 k > R[mid]）这样的比较操作时，均计为一次比较（即教材中讨论关键字比较次数时的假设方式）。若数组中不存在关键字为 k 的元素，则返回 -1 表示查找失败。

【输入形式】

输入包含两行：
第一行有两个整数，第一个整数 n 表示数组中元素的个数（n > 1），第二个整数 k 表示要查找的目标关键字。
第二行有 n 个整数，这些整数构成一个已经排好序（升序排列）的数组，各整数之间用空格分隔。

【输出形式】
输出一个整数，表示成功查找到关键字为 k 的元素所需的比较次数；若关键字 k 不存在于数组中，则输出 -1。



【样例输入】

8 6
1 3 5 6 7 9 11 13
【样例输出】

3


【解释】

在有序数组 1 3 5 6 7 9 11 13 中查找关键字 6 。第一次计算中间位置 mid = (0 + 7) / 2 = 3 ，比较 R[3]（值为 6）和 k（值为 6），这是第 1 次比较；由于相等查找成功，但按照题目要求的比较次数统计方式，继续模拟后续折半查找步骤（实际找到就停止），第二次会进行新的区间划分并比较（即使已经找到），第三次同理，总共进行了 3 次比较操作，所以输出 3 。



【注意】

我们约定二分的基本结构如下：

int l = 0, r = n - 1;

while (l < r) {

    int mid = (l + r) / 2;

    if (check(mid)) l = mid + 1;

    else r = mid;

}

也就是说，只有一边是闭区间，另一边是开区间，每次循环中只进行 check 判断一次。
*/

#include <iostream>
#include <vector>
using namespace std;


int main () {
    int n;
    cin >> n;
    int target;
    cin >> target;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int left = 0;
    int right = n - 1;
    int result = 0;
    bool found = false;
    while (left < right) {
        int mid = (left + right) / 2;
        if (arr[mid] > target) {
            right = mid;
            result++;
        } else if (arr[mid] < target) {
            left = mid + 1;
            result++;
        } else {
            found = true;
            //left = mid + 1;
            right = mid;
            result++;
        }
    }
    cout << (found ? result : -1) << endl;
    return 0;
}