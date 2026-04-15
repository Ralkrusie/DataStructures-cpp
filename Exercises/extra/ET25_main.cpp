/*
25. 查找倒数第k个节点
查找倒数第k个节点
一、问题描述
给定一个单链表，查找并输出倒数第k个节点的值。如果k大于链表长度，输出-1。

输入为先序遍历的链表节点值，-1表示链表结束。

二、输入形式
第一行输入一个正整数k（1 ≤ k ≤ 100000）。
第二行输入若干个整数，表示链表节点值，以-1结束。

三、输出形式
输出倒数第k个节点的值。如果不存在，输出-1。

四、样例输入

2
1 2 3 4 5 -1
五、样例输出

4
六、样例说明
链表：1 → 2 → 3 → 4 → 5 → NULL
倒数第1个是5，倒数第2个是4，输出4。

七、评分标准
共6个测试用例。

八、类库使用要求
必须手动实现链表结构。要求使用双指针法（快慢指针），只遍历链表一次。可以使用iostream。
*/

#include <iostream>

class myList {
public:
    myList() : headNode(nullptr), tailNode(nullptr), size(0) {}

    ~myList() {
        clear();
    }

    void push_back(const int &x) {
        Node *newNode = new Node(x);
        if (headNode == nullptr) {
            headNode = tailNode = newNode;
        } else {
            tailNode->next = newNode;
            tailNode = newNode;
        }
        ++size;
    }

    int kthFromEnd(int k) const {
        if (k <= 0) {
            return -1;
        }

        Node *fast = headNode;
        for (int i = 0; i < k; ++i) {
            if (fast == nullptr) {
                return -1;
            }
            fast = fast->next;
        }

        Node *slow = headNode;
        while (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow == nullptr ? -1 : slow->value;
    }

    void clear() {
        while (headNode != nullptr) {
            Node *next = headNode->next;
            delete headNode;
            headNode = next;
        }
        tailNode = nullptr;
        size = 0;
    }

private:
    struct Node {
        int value;
        Node *next;
        explicit Node(const int &v) : value(v), next(nullptr) {}
    };

    Node *headNode;
    Node *tailNode;
    size_t size;
};

int main() {
    int k;
    std::cin >> k;
    myList list;
    int x;
    while (std::cin >> x && x != -1) {
        list.push_back(x);
    }
    std::cout << list.kthFromEnd(k) << '\n';
    return 0;
}