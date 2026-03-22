#include <iostream>

#include "SingleLinkedList.hpp"

bool removeDuplicates(SingleLinkedList<int> &list) {
    if (list.isEmpty()) {
        return true; 
    }

    size_t pos = 0;
    int currentData{};
    int nextData{};
    while (nextData != -1) {
        list.getAt(pos, currentData);
        list.getAt(pos + 1, nextData);
        if (currentData == nextData) {
            list.removeAt(pos + 1);
        } else {
            ++pos;
        }
    }
    return true; 
}




int main() {
    SingleLinkedList<int> List;
    int data;
    while (std::cin >> data && data != -1) {
        List.pushBack(data);
    }
    List.pushBack(-1);
    removeDuplicates(List);
    for (size_t i = 0; i < List.size() - 1; ++i) {
        int value{};
        List.getAt(i, value);
        std::cout << value << " ";
    }

    return 0;
}