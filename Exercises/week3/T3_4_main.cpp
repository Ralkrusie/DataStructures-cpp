#include <iostream>
#include "SingleLinkedList.hpp"

/*
【问题描述】

有一个整数单链表L，设计一个算法将所有负整数的元素移到其他元素的前面，分别保持负数和正数的原始相对顺序，要求在原始链表上操作，不额外新建链表。例如，L=(1,2,-1,-2,3,-3,4)，移动后L=(-1,-2,-3,1,2,3,4)。

【输入形式】

第一行输入一个正整数N，表示链表的长度

第二行输入N个整数A[i]，表示链表的元素

【输出形式】

输出一行整数，表示操作后的链表

【样例输入】

4

1 -3 -5 7

【样例输出】

-3 –5 1 7

【样例说明】

【评分标准】

保证整数在int范围内

N<100000

【类库使用要求】

不可以使用STL库函数

【说明】

需要自行定义链表，完成链表的操作，不能使用STL库
*/

int main() {
    int N;
    std::cin >> N;
    SingleLinkedList<int> list;
    for (int i = 0; i < N; ++i) {
        int data;
        std::cin >> data;
        list.pushBack(data);
    }

    list.stablePartitionLessThan(0);
    for (std::size_t i = 0; i < list.size(); ++i) {
        int value;
        list.getAt(i, value);
        std::cout << value << " ";
    }
}