/*
2. 条件反转循环队列
【问题描述】

设计一个算法，利用一个顺序栈将一个循环队列中的所有元素倒过来，使得队头变为队尾，队尾变为队头。同时队列中存在特殊标记元素（值为 -1），
这些元素在反转后必须保持原有的位置，其他元素需完全倒置。

【输入形式】

第一行输入一个整数n，表示循环队列的长度；
第二行输入n个整数，以空格分隔，表示循环队列的元素值，输入按队列的顺序给出，即第一个数是队头元素，最后一个数是队尾元素。

【输出形式】

输出一行整数，表示倒置后的队列元素，元素之间以空格分隔，新的队头在最前面，新的队尾在最后面。

【样例输入】

5

1 2 3 -1 5

【样例输出】

5 3 2 -1 1

【样例说明】
【评分标准】

【类库使用要求】

不可以使用STL中的stack、queue、vector等库函数，可以使用字符串STL处理输入。

【说明】

要求自己设计实现栈或队列类
*/

#include <iostream>

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

    int top() const{
        return topNode->value;
    };

    void display() const{
        Node *current = topNode;
        while (current) {
            std::cout << current->value << ' ';
            current = current->next;
        }
        std::cout << '\n';
    };

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
    int *queue = new int[n];
    for (int i = 0; i < n; i++){
        std::cin >> queue[i];
    }
    myStack stack;
    for (int i = 0; i < n; i++){
        if (queue[i] != -1){
            stack.push(queue[i]);
        }
    }
    for (int i = 0; i < n; i++){
        if (queue[i] == -1){
            std::cout << "-1 ";
        } else {
            std::cout << stack.top() << ' ';
            stack.pop();
        }
    }
    std::cout << '\n';
    delete[] queue;
    return 0;
}