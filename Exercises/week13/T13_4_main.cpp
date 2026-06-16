/*
4. 第九章第5题
【问题描述】

有一个递增整数序列R且所有整数不相同，设计一个高效的算法判断是否存在某一整数i恰好存放在R[i]中。


【输入形式】

第一行输入一个整数 n，表示序列长度。

第二行输入 n 个整数，按升序排列，表示序列 R。


【输出形式】

如果存在某个 i 满足 R[i] == i，输出 Yes。

否则，输出 No。


【样例输入】

5

-3 -1 1 3 4


【样例输出】

Yes


【样例说明】

索引为 3 的元素值为 R[3] = 3，满足条件。
*/
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int value;
    for (int i = 0; i < n; i++) {
        cin >> value;
        if (value == i) {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
    return 0;
}