/*
三、输出形式
输出"YES"或"NO"，表示链表是否有环。

四、样例输入

4
1 2
2 3
3 4
4 2
五、样例输出

YES
六、样例说明
链表结构：1 → 2 → 3 → 4 → 2（形成环：2→3→4→2）

七、评分标准
共6个测试用例。

测试用例1-3：小规模数据，哈希法可过

测试用例4-6：大规模数据，要求使用快慢指针法（Floyd判圈算法）

八、类库使用要求
可以使用iostream、vector。要求使用Floyd判圈算法，空间复杂度O(1)。
*/

#include <iostream>
#include <vector>

int main() {
    int size;
    int ignored;
    std::cin >> size;
    std::vector<int> numbers(size + 1);
    numbers[0] = 1; 
    for (int i = 1; i <= size; ++i) {
        std::cin >> ignored >> numbers[i];
    }

    int slow = numbers[0];
    int fast = numbers[0];
    int oldFast = numbers[0];
    while (fast != 0 && oldFast != 0) {
        if (fast > size) {
            break;
        }
        oldFast = numbers[fast];
        if (oldFast > size) {
            break;
        }
        fast = numbers[oldFast];
        slow = numbers[slow];
        if (slow == fast) {
            std::cout << "YES" << std::endl;
            return 0;
        }
    }
    std::cout << "NO" << std::endl;
    return 0;
}
