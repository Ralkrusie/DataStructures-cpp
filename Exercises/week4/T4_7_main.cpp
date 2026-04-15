/*退格问题*/
#include <iostream>
#include <string>
#include <stdexcept>

class Mystack {
public:
    Mystack():topNode(nullptr){}
    ~Mystack(){
        clear();
    }

    void push(const char& value){
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop(){
        if (topNode){
            Node* outNode = topNode;
            topNode = topNode->next;
            delete outNode;
        }
    }

    char top() const {
        if (topNode){
            return topNode->data;
        }
        // top on an empty stack is invalid, so report it explicitly.
        throw std::out_of_range("Mystack::top called on empty stack");
    }

    void clear(){
        while (!isEmpty()){
            pop();
        }
    };

    bool isEmpty(){
        return !topNode;
    }

private:
    struct Node {
        char data;
        Node* next;
        explicit Node(const char& value):data(value), next(nullptr){}
    };
    Node* topNode;
};

int main(){
    Mystack st;
    std::string input;
    std::cin >> input;
    for (const char& ch : input){
        if (ch == '#'){
            st.pop();
        } else {
            st.push(ch);
        }
    }
    Mystack output;
    while (!st.isEmpty()){
        output.push(st.top());
        st.pop();
    }
    while(!output.isEmpty()){
        std::cout << output.top();
        output.pop();
    }
    st.clear();
    output.clear();
}