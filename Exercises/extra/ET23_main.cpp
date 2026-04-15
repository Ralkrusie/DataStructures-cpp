/*
23. 单链表逆置-递归法
单链表逆置-递归法
一、问题描述
给定一个单链表，将其原地逆置。要求使用递归法实现。

输入为先序遍历的链表节点值，-1表示链表结束（NULL）。

二、输入形式
一行若干个整数，表示链表节点值，以-1结束。

三、输出形式
输出逆置后的链表节点值，以空格分隔，最后不输出-1。

四、样例输入

1 2 3 4 5 -1
五、样例输出

5 4 3 2 1
六、样例说明
递归逆置过程：

递归到链表末尾，返回尾节点作为新头

每层递归中：head->next->next = head，将下一个节点的next指向当前节点

head->next = NULL，断开当前节点的next

返回新头

七、评分标准
共6个测试用例。

测试用例1-3：小规模数据

测试用例4-6：大规模数据，注意递归深度可能导致栈溢出，题目保证n ≤ 10000

八、类库使用要求
必须手动实现链表结构，使用递归实现。可以使用iostream。
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

    void reverseRecursive() {
        if (headNode == nullptr || headNode->next == nullptr) {
            return;
        }
        Node *oldHead = headNode;
        headNode = reverseNodes(headNode);
        tailNode = oldHead;
    }

    void display() const {
        Node *current = headNode;
        if (current != nullptr) {
            std::cout << current->value;
            current = current->next;
            while (current != nullptr) {
                std::cout << ' ' << current->value;
                current = current->next;
            }
        }
        std::cout << '\n';
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

    static Node *reverseNodes(Node *head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        Node *newHead = reverseNodes(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }

    Node *headNode;
    Node *tailNode;
    size_t size;
};

int main() {
    myList list;
    int x;
    while (std::cin >> x && x != -1) {
        list.push_back(x);
    }
    list.reverseRecursive();
    list.display();
    return 0;
}