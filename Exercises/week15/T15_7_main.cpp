/*
7. POJ1065—木棍
【问题描述】


一堆n根木棍，每个木棍的长度和重量是预先已知的。这些木棒将由木工机械加工。机器预处理木棍需要一些时间，称为设置时间。设置时间与清理操作以及更换机器中的工具和形状有关。加工机器的设置时间规定如下：

（a）第一个木棍的设置时间为1分钟。

（b）在加工（l，w）木棍（表示长度为l和重量为w的木棍）之后，如果遇到（l'，w'）木棍，并且有l≤l'，w≤w'，则机器加工（l'，w'）木棍不需要设置时间，否则，需要1分钟进行设置时间。

你要找到加工给定的n根木棍的最短设置时间。例如，如果你有5个长度和重量对分别为（9，4），（2，5），（1、2），（5、3）和（4,1）的木棍，则最小设置时间应该是2分钟，因为正确的加工顺序是（4，1），（5，3），（9，4），（1，2），（2，5）。



【输入形式】


每个测试用例由两行组成，第一行是整数n（1≤n≤5000），表示木棍的数量，第二行包含2n个正整数l1，w1，l2，w2，…，ln，wn，每个整数最大为10000，其中li和wi分别是第i个木棍的长度和重量。2n个整数由一个或多个空格分隔。



【输出形式】


每行以分钟为单位输出最短设置时间。



【样例输入】


5

4 9 5 2 2 1 3 5 1 4





【样例输出】

       2



【样例说明】

    对输入的5根木棍，其最短设置时间为2。测试数据存放在in.txt文件中。



【评分标准】

    共10个测试用例，每通过一个测试得10分。
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Stick {
    int l, w;
};

int main() {
    ifstream fin("in.txt");
    int n;
    while (fin >> n) {
        vector<Stick> sticks(n);
        for (int i = 0; i < n; ++i) {
            fin >> sticks[i].l >> sticks[i].w;
        }
        // 按长度升序，长度相等时按重量升序
        sort(sticks.begin(), sticks.end(), [](const Stick& a, const Stick& b) {
            if (a.l != b.l) return a.l < b.l;
            return a.w < b.w;
        });

        // 对重量数组求最长严格递减子序列(LDS)长度 = 最小设置时间
        // 用二分优化到 O(n log n)
        vector<int> weights(n);
        for (int i = 0; i < n; ++i) {
            weights[i] = sticks[i].w;
        }
        vector<int> tails;
        for (int w : weights) {
            // 在 tails 中找第一个 < w 的位置（严格递减）
            int left = 0, right = (int)tails.size();
            while (left < right) {
                int mid = (left + right) / 2;
                if (tails[mid] < w) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }
            if (left == (int)tails.size()) {
                tails.push_back(w);
            } else {
                tails[left] = w;
            }
        }
        cout << (int)tails.size() << endl;
    }
    return 0;
}