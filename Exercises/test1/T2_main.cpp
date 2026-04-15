/*偶数出栈*/
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
    st.display();
}