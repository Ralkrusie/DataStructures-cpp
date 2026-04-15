/*
【问题描述】

给定一个字符串str，设计一个算法，采用顺序栈判断str是否为形如“序列1@序列2”的合法字符串，其中序列2是序列1的逆序，在str中恰好只有一个@字符。


【输入形式】

给定一个字符串str。


【输出形式】

输出为一行，若合法则输出1，否则输出0。

【样例输入】

abc@cba



【样例输出】

1


【样例说明】

序列1为 abc，序列2为 cba，序列2是序列1的逆序，且仅有一个 @，因此合法。



【评分标准】




【类库使用要求】

不可以使用STL中的stack、queue、vector等库函数，可以使用字符串STL处理输入。

【说明】

要求自己设计实现栈或队列类
*/
#include <iostream>
#include <string>

class myStack{
public:
    myStack():topNode(nullptr), size(0) {};

    ~myStack(){
        clear();
    };

    void push(const char &x){
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

    char top() const{
        return topNode->value;
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
    char value;
    Node *next;
    explicit Node(const char &x) : value(x), next(nullptr) {}
    };
    Node *topNode;
    size_t size;
};

int main() {
    std::string input;
    std::getline(std::cin, input);

    if (input == "@") {
    std::cout << "1\n";
    return 0;
    }

    myStack st;
    size_t index = 0;
    while (input[index] != '@') {
        st.push(input[index]);
        index++;
    }
    index++;
    while (index < input.size()) {
        if (st.getSize() == 0 || st.top() != input[index]) {
            std::cout << "0\n";
            return 0;
        } else {
            st.pop();
            index++;
        }
    }
    if (st.getSize() != 0) {
        std::cout << "0\n";
        return 0;
    }
    std::cout << "1\n";
    return 0;
}
