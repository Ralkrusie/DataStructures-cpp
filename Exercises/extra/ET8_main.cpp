/*链栈基本操作*/
#include <iostream>
#include <string>

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
        if (isEmpty()){
            return;
        }
        Node *oldTop = topNode;
        topNode = topNode->next;
        delete oldTop;
        --size;
    };

    int top() const{
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

    bool isEmpty() const {
        return size == 0;
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
    myStack st;
    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++){
        std::string operation;
        std::cin >> operation;
        if (operation == "PUSH"){
            int data;
            std::cin >> data;
            st.push(data);
        } else if (operation == "POP"){
            if (st.isEmpty()){
                std::cout << "EMPTY\n";
            } else {
                std::cout << st.top() << std::endl;
                st.pop();
            }
        } else if (operation == "TOP"){
            if (st.isEmpty()){
                std::cout << "EMPTY\n";
            } else {
                std::cout << st.top() << std::endl;
            }
        } else if (operation == "IS_EMPTY"){
            if (st.isEmpty()){
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }
    }
}