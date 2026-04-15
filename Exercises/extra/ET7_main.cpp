/*
双端队列实现

PUSH_FRONT x：在队头插入元素x

PUSH_BACK x：在队尾插入元素x

POP_FRONT：移除队头元素，队空输出"EMPTY"

POP_BACK：移除队尾元素，队空输出"EMPTY"

FRONT：查看队头元素，队空输出"EMPTY"

BACK：查看队尾元素，队空输出"EMPTY"
*/

#include <iostream>
#include <deque>


int main(){
    int m;
    std::cin >> m;
    std::deque<int> doubleEndedDeque;
    for (int i = 0; i < m; i++){
        std::string operation;
        std::cin >> operation;
        if (operation == "PUSH_FRONT"){
            int data;
            std::cin >> data;
            doubleEndedDeque.push_front(data);

        } else if(operation == "PUSH_BACK"){
            int data;
            std::cin >> data;
            doubleEndedDeque.push_back(data);
        } else if(operation == "POP_FRONT"){
            if (doubleEndedDeque.empty()){
                std::cout << "EMPTY\n";
            } else
            doubleEndedDeque.pop_front();
        } else if(operation == "POP_BACK"){
            if (doubleEndedDeque.empty()){
                std::cout << "EMPTY\n";
            } else
            doubleEndedDeque.pop_back();
        } else if(operation == "FRONT"){
            if (doubleEndedDeque.empty()){
                std::cout << "EMPTY\n";
            } else
            std::cout << doubleEndedDeque.front();
        } else if(operation == "BACK"){
            if (doubleEndedDeque.empty()){
                std::cout << "EMPTY\n";
            } else
            std::cout << doubleEndedDeque.back();
        } else if(operation == "SIZE"){
            if (doubleEndedDeque.empty()){
                std::cout << "0\n";
            } else
            std::cout << doubleEndedDeque.size() << std::endl;
        } 
    }
}