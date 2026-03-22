#include <iostream>
#include <string>
#include <utility>

#include "DoubleLinkedList.hpp"

int main() {
    DoubleLinkedList<std::string> list;
    list.pushBack("Hello");
    list.pushBack("World");
    list.pushFront("Start");

    std::string value;
    if (list.getAt(1, value)) {
        std::cout << "Element at index 1: " << value << std::endl; // Should print "Hello"
    }

    if (list.getAtFromBack(0, value)) {
        std::cout << "Element at reverse index 0: " << value << std::endl; // Should print "World"
    }

    list.insertAt(2, "Inserted");
    if (list.getAt(2, value)) {
        std::cout << "Element at index 2: " << value << std::endl; // Should print "Inserted"
    }

    list.removeAt(1);
    if (list.getAt(1, value)) {
        std::cout << "Element at index 1 after removal: " << value << std::endl; // Should print "Inserted"
    }

    return 0;
}