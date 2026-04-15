/*
24. 单链表基本操作-创建插入删除遍历
单链表基本操作-创建插入删除遍历
一、问题描述
实现一个带头结点的单链表，支持以下操作：

CREATE n：创建一个包含n个元素的链表，元素值依次为1到n

INSERT k x：在第k个位置（从1开始）插入元素x

DELETE k：删除第k个位置的元素

PRINT：输出链表所有元素

二、输入形式
第一行输入一个正整数m（1 ≤ m ≤ 1000），表示操作数量。
接下来m行，每行一个操作，格式如上所述。

三、输出形式
对于每个PRINT操作，输出一行，包含链表的所有元素，用空格分隔。如果链表为空，输出"EMPTY"。

四、样例输入

8
CREATE 3
PRINT
INSERT 2 5
PRINT
DELETE 3
PRINT
DELETE 1
PRINT
五、样例输出

1 2 3
1 5 2 3
1 5 3
5 3
六、样例说明
操作过程：

CREATE 3：创建链表[1,2,3]

PRINT：输出1 2 3

INSERT 2 5：在第2位插入5，链表变为[1,5,2,3]

PRINT：输出1 5 2 3

DELETE 3：删除第3位（值为2），链表变为[1,5,3]

PRINT：输出1 5 3

DELETE 1：删除第1位（值为1），链表变为[5,3]

PRINT：输出5 3

七、评分标准
共6个测试用例。

八、类库使用要求
必须手动实现链表结构，禁止使用STL list。可以使用iostream。
*/
#include <iostream>
#include <sstream>
#include <string>

class myList {
public:
    myList() : headNode(0), size(0) {}

    ~myList() {
        clear();
    }

    void createList(int n) {
        clear();
        Node *tail = &headNode;
        for (int i = 1; i <= n; ++i) {
            tail->next = new Node(i);
            tail = tail->next;
        }
        size = n;
    }

    void insertAt(int k, int x) {
        Node *prev = &headNode;
        for (int pos = 1; pos < k; ++pos) {
            prev = prev->next;
        }
        Node *node = new Node(x);
        node->next = prev->next;
        prev->next = node;
        ++size;
    }

    void deleteAt(int k) {
        Node *prev = &headNode;
        for (int pos = 1; pos < k; ++pos) {
            prev = prev->next;
        }
        Node *target = prev->next;
        prev->next = target->next;
        delete target;
        --size;
    }

    void display() const {
        if (headNode.next == nullptr) {
            std::cout << "EMPTY\n";
            return;
        }

        bool first = true;
        for (Node *p = headNode.next; p != nullptr; p = p->next) {
            if (!first) {
                std::cout << ' ';
            }
            std::cout << p->value;
            first = false;
        }
        std::cout << '\n';
    }

    void clear() {
        Node *p = headNode.next;
        while (p != nullptr) {
            Node *next = p->next;
            delete p;
            p = next;
        }
        headNode.next = nullptr;
        size = 0;
    }

private:
    struct Node {
        int value;
        Node *next;
        explicit Node(int v = 0) : value(v), next(nullptr) {}
    };

    Node headNode;
    size_t size;
};

int main() {
    int m;
    std::cin >> m;
    std::string line;
    std::getline(std::cin, line);

    myList list;

    for (int i = 0; i < m; ++i) {
        std::getline(std::cin, line);
        if (line.empty()) {
            --i;
            continue;
        }

        std::stringstream ss(line);
        std::string op;
        ss >> op;

        if (op == "CREATE") {
            int n;
            ss >> n;
            list.createList(n);
        } else if (op == "INSERT") {
            int k, x;
            ss >> k >> x;
            list.insertAt(k, x);
        } else if (op == "DELETE") {
            int k;
            ss >> k;
            list.deleteAt(k);
        } else if (op == "PRINT") {
            list.display();
        }
    }

    return 0;
}