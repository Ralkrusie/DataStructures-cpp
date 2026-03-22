#pragma once

#include <cstddef> // for std::size_t
#include <utility> // for std::move

// 栈模板：用 T 表示栈里存储的数据类型。
// 栈是一种后进先出（LIFO）的数据结构，支持在一端进行插入和删除操作。
//---------------------------声明----------------------------
template<typename T>
class LinkedStack {
public:
    // 基本生命周期：遵循“规则五（Rule of Five）”，避免浅拷贝导致重复释放。
    LinkedStack();
    LinkedStack(const LinkedStack &other);
    LinkedStack &operator=(const LinkedStack &other);
    LinkedStack(LinkedStack &&other) noexcept;
    LinkedStack &operator=(LinkedStack &&other) noexcept;
    ~LinkedStack();

    // 栈顶插入/删除：时间复杂度 O(1)。
    void push(const T &value);
    bool pop(T &outValue);

    // 读取栈顶元素：采用输出参数风格，便于表达“可能失败”。
    bool top(T &outValue) const;

    // 清空栈并释放节点。
    void clear();

    // 栈大小和空栈判定：O(1)，因为我们维护了 m_size 变量。
    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] bool isEmpty() const;

private:
    // 栈节点：保存数据和指向下一个节点的指针。 
    struct Node {
        T m_value;
        Node *m_next;

        explicit Node(const T &value) : m_value(value), m_next(nullptr) {
        }
    };

    Node *m_top;
    std::size_t m_size;
    [[nodiscard]] Node *getNodeAt(std::size_t index);
    [[nodiscard]] const Node *getNodeAt(std::size_t index) const;
    // 深拷贝/资源接管的内部工具函数。
    void copyFrom(const LinkedStack &other);
    void moveFrom(LinkedStack &other) noexcept;
};

//---------------------------实现----------------------------
template<typename T>
LinkedStack<T>::LinkedStack() : m_top(nullptr), m_size(0) {
}

template<typename T>
LinkedStack<T>::LinkedStack(const LinkedStack &other) : m_top(nullptr), m_size(0) {
    copyFrom(other);
}

template<typename T>
LinkedStack<T> &LinkedStack<T>::operator=(const LinkedStack &other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
LinkedStack<T>::LinkedStack(LinkedStack &&other) noexcept : m_top(nullptr), m_size(0) {
    moveFrom(other);
}

template<typename T>
LinkedStack<T> &LinkedStack<T>::operator=(LinkedStack &&other) noexcept {
    if (this != &other) {
        clear();
        moveFrom(other);
    }
    return *this;
}

template<typename T>
LinkedStack<T>::~LinkedStack() {
    clear();
}

template<typename T>
void LinkedStack<T>::push(const T &value) {
    Node *newNode = new Node(value);
    newNode->m_next = m_top;
    m_top = newNode;
    ++m_size;
}

template<typename T>
bool LinkedStack<T>::pop(T &outValue) {
    if (isEmpty()) {
        return false;
    }
    Node *oldTop = m_top;
    outValue = std::move(oldTop->m_value);
    m_top = oldTop->m_next;
    delete oldTop;
    --m_size;
    return true;
}

template<typename T>
bool LinkedStack<T>::top(T &outValue) const {
    if (isEmpty()) {
        return false;
    }
    outValue = m_top->m_value;
    return true;
}

template<typename T>
void LinkedStack<T>::clear() {
    while (m_top) {
        Node *next = m_top->m_next;
        delete m_top;
        m_top = next;
    }
    m_size = 0;
}

template<typename T>
std::size_t LinkedStack<T>::size() const {
    return m_size;
}

template<typename T>
bool LinkedStack<T>::isEmpty() const {
    return m_size == 0;
}

template<typename T>
typename LinkedStack<T>::Node *LinkedStack<T>::getNodeAt(std::size_t index) {
    if (index >= m_size) {
        return nullptr;
    }
    Node *current = m_top;
    for (std::size_t i = 0; i < index; ++i) {
        current = current->m_next;
    }
    return current;
}

template<typename T>
const typename LinkedStack<T>::Node *LinkedStack<T>::getNodeAt(std::size_t index) const {
    if (index >= m_size) {
        return nullptr;
    }
    const Node *current = m_top;
    for (std::size_t i = 0; i < index; ++i) {
        current = current->m_next;
    }
    return current;
}

template<typename T>
void LinkedStack<T>::copyFrom(const LinkedStack &other) {
    if (other.isEmpty()) {
        return;
    }
    // 先复制第一个节点，确保 m_top 不为 nullptr。
    m_top = new Node(other.m_top->m_value);
    Node *currentThis = m_top;
    const Node *currentOther = other.m_top->m_next;

    while (currentOther) {
        currentThis->m_next = new Node(currentOther->m_value);
        currentThis = currentThis->m_next;
        currentOther = currentOther->m_next;
    }
    m_size = other.m_size;
}

template<typename T>
void LinkedStack<T>::moveFrom(LinkedStack &other) noexcept {
    m_top = other.m_top;
    m_size = other.m_size;
    other.m_top = nullptr;
    other.m_size = 0;
}
