#include <iostream>
#include "SingleLinkedList.hpp"


int main() {
    size_t k;
    std::cin >> k;
    int data;
    SingleLinkedList<int> list;
    while (std::cin >> data) {
        list.pushBack(data);
        if (data == -1) {
            break;
        }
    }
    if (k <= 0 || k > list.size()) {
        std::cout << -1 << std::endl;
        return 0;
    }
    int slow{-1};
    size_t fast{k - 1};
    int currentData{};
    list.getAt(fast, currentData);
    while (currentData != -1) {
        fast++;
        slow++;
        list.getAt(fast, currentData);
    }
    list.getAt(slow, currentData);
    std::cout << currentData << std::endl;
    return 0;
}