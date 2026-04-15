/*
【问题描述】

假设有一个链栈st，设计一个算法，出栈从栈顶开始的第k个结点。


【输入形式】

1.程序首先会读取一个整数n，表示链栈中初始的元素个数。

2.接下来读取n个整数，表示链栈中的元素（从栈顶到栈底依次输入）。

3.最后读取一个整数k，表示要出栈的结点的位置（从栈顶开始计数）。



【输出形式】

1.如果成功出栈第k个结点，输出该结点的值。

2.如果k超出链栈的长度或k不合法（如 k <= 0），输出 error。

3.输出出栈操作后的链栈内容（从栈顶到栈底）。



【样例输入】

4

1 2 3 4

2



【样例输出】

2

1 3 4



【样例说明】

1.初始链栈内容为 1 -> 2 -> 3 -> 4（栈顶为 1，栈底为 4）。

2.删除从栈顶开始的第 2 个结点（即值为 2 的结点）。

3.删除后链栈内容为 1 -> 3 -> 4，并输出删除的结点值 2。



【评分标准】



【类库使用要求】

不可以使用STL中的stack、queue、vector等库函数，可以使用字符串STL处理输入。

【说明】

要求自己设计实现栈或队列类
*/
#include <iostream>
#include <cstddef>

class myStack{
public:
    myStack():topNode(nullptr), size(0) {};

    ~myStack(){
        clear();
    };

    void push(const int &x){
        Node *newNode = new Node(x);
        newNode->next = topNode;
        topNode = newNode;
        ++size;
    };

    void pop(){
        Node *oldTop = topNode;
        topNode = topNode->next;
        delete oldTop;
        --size;
    };

    void pop_at(size_t index) {
        if (index == 0) {
            pop();
            return;
        }
        myStack helper;
        for (size_t i = 0; i < index; i++) {
            helper.push(this->top());
            this->pop();
        }
        this->pop();
        for (size_t i = 0; i < index; i++) {
            this->push(helper.top());
            helper.pop();
        }
    }

    int top() const{
        return topNode->value;
    };

    void display() const {
        Node *current = topNode;
        if (current) {
            std::cout << current->value;
            current = current->next;
            while (current) {
                std::cout << ' ' << current->value;
                current = current->next;
            }
        }
        std::cout << '\n';
    }

    void clear(){
        while (topNode) {
            Node *next = topNode->next;
            delete topNode;
            topNode = next;
        }
        size = 0;
    };

    size_t getSize() const{
        return size;
    };

    void reverse() {
        Node *prev = nullptr;
        Node *current = topNode;
        while (current) {
            Node *next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        topNode = prev;
    };

    int at(size_t index) const {
        if (index == 0) {
            return top();
        }
        Node *current = topNode;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        return current->value;
    }

private:
    struct Node {
    int value;
    Node *next;
    explicit Node(const int &x) : value(x), next(nullptr) {}
    };
    Node *topNode;
    size_t size;
};




int main(){
    int n;
    std::cin >> n;
    myStack st;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        st.push(x);
    }
    st.reverse();

    int k;
    std::cin >> k;
    if (k <= 0 || k > static_cast<int>(st.getSize())) {
        std::cout << "error\n";
        return 0;
    }
    std::cout << st.at(k - 1) << std::endl;
    st.pop_at(k - 1);
    if (st.getSize() != 0)
        st.display();
    return 0;
}