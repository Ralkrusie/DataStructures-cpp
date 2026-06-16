/*
1. 第九章第4题
【问题描述】

假设关键字有序表为整数，修改基本折半查找算法，给出在成功查找到关键字k时的查找序列。


【输入形式】

第一行一个整数 n，表示有序表的长度；
第二行 n 个升序排列的整数，表示有序表内容；
第三行一个整数 k，表示要查找的关键字。


【输出形式】

若查找成功，输出查找序列，即每一步访问的中间元素，空格分隔。
若查找失败，仅输出一行：Not Found


【样例输入】

7  

1 3 5 7 9 11 13  

9


【样例输出】

7 11 9



【样例说明】

查找过程如下：
第一次比较中间元素 7（位置3）→ 小于9，查右边
第二次比较中间元素 11 → 大于9，查左边
第三次比较中间元素 9 → 成功找到
访问序列为：7 11 9


【评分标准】


*/

#include <iostream>
#include <vector>
using namespace std;

void f(const vector<int>& nums, int target) {
    vector<int> path;
    int left = 0;
    int right = nums.size() - 1;
    int compare;
    while (left <= right) {
        compare = (left + right) / 2;
        path.push_back(nums[compare]);
        if (nums[compare] == target) {
            for (int num : path) {
                cout << num << ' ';
            }
            return;
        } else if (nums[compare] < target) {
            left = compare + 1;
        } else {
            right = compare - 1;
        }
    }
    cout << "Not Found\n";
}


int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    int k;
    cin >> k;

    f(nums, k);
}