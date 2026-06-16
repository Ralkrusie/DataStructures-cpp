/*
3. 第六章 递归算法 删除指定值节点
[问题描述]
设计一个递归算法，在不带表头结点的整数单链表中删除所有值等于给定值x的节点。链表中的元素由用户输入确定。
要求用链表保存数据，并删除指定节点。
[输入形式]
第一行是一个整数n，表示链表的长度；
第二行是n个用空格分隔的整数，表示链表中的值；
第三行是一个整数x，表示需要删除节点的值。

[输出形式]
按修改后的链表顺序输出所有剩余节点的值。如果链表为空，则只输出"-1"。

[输入样例]
5
1 2 3 2 4
2

[输出样例]
1 3 4

[样例说明]
删除值为2的所有节点后，链表中剩余的元素是{1, 3, 4}。


[说明]
要求用链表完成算法设计，可以使用STL库函数。
*/

#include <iostream>
#include <forward_list>
#include <cstddef>
#include <vector>


class myList {
private:
    struct Node {
        int value;
        Node* nextNode;
        explicit Node(const int& x): value(x), nextNode(nullptr) {}
    };
    size_t size;
    Node* headNode;

public:
    explicit myList(): headNode(nullptr), size(0) {}
    ~myList() {
        clear();
    }

    void clear() {
        Node* current = headNode;
        while (current != nullptr) {
            Node* temp = current;
            current = current->nextNode;
            delete temp;
        }
        size = 0;
    }

    void pushFront(const int& x) {
        Node* newNode = new Node(x);
        if (headNode == nullptr) {
            headNode = newNode;
        } else {
            newNode->nextNode = headNode;
            headNode = newNode;
        }
        size++;
    }

    Node* filterFromNode(const int& x, Node* current) { 
        if (current == nullptr) {
            return nullptr;
        }
        current->nextNode = filterFromNode(x, current->nextNode);
        if (current->value == x) {
            Node* next = current->nextNode;
            delete current;
            size--;
            return next;
        }
        return current;
    }

    void filter(const int& x) {
        headNode = filterFromNode(x, headNode);
    }

    void printReverse() {
        std::vector<int> result;
        Node* current = headNode;
        if (current == nullptr) {
            std ::cout << "-1\n";
            return;
        }
        while (current != nullptr){
            result.push_back(current->value);
            current = current->nextNode;
        }
        for (size_t i = result.size(); i > 0; i--) {
            std ::cout << result[i - 1] << ' ';
        }
    }

};



int main() {
    int n;
    std::cin >> n;
    myList list;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        list.pushFront(x);
    }
    int target;
    std::cin >> target;

    list.filter(target);
    list.printReverse();
}