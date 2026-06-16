/*
3. 第六章 第6题
【问题描述】

设有一个不带表头结点的整数单链表p，设计一个递归算法getNo(p,
x)查找第一个值为x的结点的序号（假设首结点的序号为0），没有找到时返回一1。

【输入形式】

第一行：链表长度

第二行：链表 元素以空格隔开

第三行：查找的值x
【输出形式】

结点序号
【样例输入】

3

10 20 30

10

【样例输出】

0
*/

#include <cstddef>
#include <iostream>
#include <type_traits>

template <typename T> class myList {
  private:
    struct Node;
    
  public:

    myList() : headNode(T()), tailNode(&headNode), size(0) {}

    ~myList() { clear(); }

    void pushBack(const T &x) {
        Node *newNode = new Node(x);
        tailNode->next = newNode;
        tailNode = newNode;
        ++size;
    }

    void pushFront(const T &x) {
        Node *newNode = new Node(x);
        newNode->next = headNode.next;
        headNode.next = newNode;
        if (tailNode == &headNode) {
            tailNode = newNode;
        }
        ++size;
    }

    void popFront() {
        if (headNode.next == nullptr) {
            return;
        }
        Node *oldFront = headNode.next;
        headNode.next = oldFront->next;
        if (oldFront == tailNode) {
            tailNode = &headNode;
        }
        delete oldFront;
        --size;
    }

    void popBack() {
        if (headNode.next == nullptr) {
            return;
        }
        Node *prev = &headNode;
        while (prev->next != tailNode) {
            prev = prev->next;
        }
        delete tailNode;
        tailNode = prev;
        tailNode->next = nullptr;
        --size;
    }

    void clear() {
        Node *current = headNode.next;
        while (current != nullptr) {
            Node *next = current->next;
            delete current;
            current = next;
        }
        headNode.next = nullptr;
        tailNode = &headNode;
        size = 0;
    }

    size_t getSize() const { return size; }

    bool isEmpty() const { return size == 0; }

    void getNoStart(const T &x, const myList& list, int& result) const {
        getNo(x, list.headNode.next, result);
    }

    void getNo(const T &x, const Node* head, int& result) const {
        if (head == nullptr) {
            result = -1;
            return;
        }
        if (head->value == x) {
            result = 0;
            return;
        }
        getNo(x, head->next, result);
        if (result != -1) {
            ++result;
        }
    }


  private:
    struct Node {
        T value;
        Node *next;
        explicit Node(const T &v = T()) : value(v), next(nullptr) {}
    };

    void moveFrom(myList<T> &other) {
        if (other.headNode.next == nullptr) {
            return;
        }
        headNode.next = other.headNode.next;
        tailNode = other.tailNode;
        size = other.size;
        other.headNode.next = nullptr;
        other.tailNode = &other.headNode;
        other.size = 0;
    }

    Node headNode;
    Node *tailNode;
    size_t size;
};

int main() {
    myList<int> list;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;
        list.pushBack(value);
    }
    int x;
    std::cin >> x;

    int result = -1;
    list.getNoStart(x, list, result);
    std::cout << result << '\n';
    return 0;
}
