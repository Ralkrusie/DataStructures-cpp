#pragma once

#include <cstddef> // for std::size_t
#include <utility> // for std::move

// 双链表模板：用 T 表示节点里存储的数据类型。
// 相较单链表，增加了 prev 指针，支持双向遍历和更高效的尾部操作。

//---------------------------声明----------------------------
template<typename T>
class DoubleLinkedList {
public:
    // 基本生命周期：遵循“规则五（Rule of Five）”，避免浅拷贝导致重复释放。
    DoubleLinkedList();
    DoubleLinkedList(const DoubleLinkedList &other);
    DoubleLinkedList &operator=(const DoubleLinkedList &other);
    DoubleLinkedList(DoubleLinkedList &&other) noexcept;
    DoubleLinkedList &operator=(DoubleLinkedList &&other) noexcept;
    ~DoubleLinkedList();

    // 头插/尾插：时间复杂度 O(1)。
    void pushFront(const T &value);
    void pushBack(const T &value);
    // 在 index 位置插入，允许 index == size()（等价于尾插）。
    // 成功返回 true，越界返回 false。平均/最坏复杂度 O(n)。
    bool insertAt(std::size_t index, const T &value);
    // 删除 index 位置节点。成功返回 true，越界返回 false。复杂度 O(n)。
    bool removeAt(std::size_t index);

    // 读取/修改指定下标元素：读取采用输出参数风格，便于表达“可能失败”。
    bool getAt(std::size_t index, T &outValue) const;
    bool setAt(std::size_t index, const T &value);

    // 清空链表并释放节点。
    void clear();

    //链表长度和空表判定：O(1)，因为我们维护了 m_size 变量。
    // [[nodiscard]] 提醒调用者不要忽略返回值。
    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] bool isEmpty() const;

private:
    // 链表节点：保存数据和指向前后节点的指针。
    struct Node {
        T m_value;
        Node *m_prev;
        Node *m_next;

        explicit Node(const T &value) : m_value(value), m_prev(nullptr), m_next(nullptr) {
        }
    };

    Node *m_head;
    Node *m_tail;
    std::size_t m_size;

    [[nodiscard]] Node *getNodeAt(std::size_t index);
    [[nodiscard]] const Node *getNodeAt(std::size_t index) const;
    // 深拷贝/资源接管的内部工具函数。
    void copyFrom(const DoubleLinkedList &other);
    void moveFrom(DoubleLinkedList &other) noexcept;
};

//---------------------------定义----------------------------
// 构造时初始化空链表状态。
template<typename T>
DoubleLinkedList<T>::DoubleLinkedList() : m_head(nullptr), m_tail(nullptr), m_size(0) {
}

// 复制构造：通过 copyFrom 实现深拷贝。
template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList &other) : DoubleLinkedList() {
    copyFrom(other);
}

// 复制赋值：先清空自身，再深拷贝。
template<typename T>
DoubleLinkedList<T> &DoubleLinkedList<T>::operator=(const DoubleLinkedList &other) {
    if (this == &other) {
        return *this;
    }

    clear();
    copyFrom(other);
    return *this;
}

// 移动构造：通过 moveFrom 实现资源转移。
template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList &&other) noexcept : DoubleLinkedList() {
    moveFrom(other);
}

// 移动赋值：先释放自身，再接管 other 资源。
template<typename T>
DoubleLinkedList<T> &DoubleLinkedList<T>::operator=(DoubleLinkedList &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    clear();
    moveFrom(other);
    return *this;
}

// 析构时统一走 clear，确保节点不会泄漏。
template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
    clear();
}

// 头插：新节点 prev 指向 nullptr，next 指向原头节点，再更新头指针。
template<typename T>
void DoubleLinkedList<T>::pushFront(const T &value) {
    Node *newNode = new Node(value);
    newNode->m_next = m_head;

    if (m_head != nullptr) {
        m_head->m_prev = newNode;
    }
    m_head = newNode;

    if (m_tail == nullptr) {
        m_tail = newNode;
    }

    ++m_size;
}

// 尾插：新节点 prev 指向原尾节点，next 指向 nullptr，再更新尾指针。
template<typename T>
void DoubleLinkedList<T>::pushBack(const T &value) {
    Node *newNode = new Node(value);
    newNode->m_prev = m_tail;

    if (m_tail != nullptr) {
        m_tail->m_next = newNode;
    }
    m_tail = newNode;

    if (m_head == nullptr) {
        m_head = newNode;
    }

    ++m_size;
}

// 在任意位置插入：核心是先找到前驱节点，再改链。
template<typename T>
bool DoubleLinkedList<T>::insertAt(std::size_t index, const T &value) {
    if (index > m_size) {
        return false;
    }

    if (index == 0) {
        pushFront(value);
        return true;
    }

    if (index == m_size) {
        pushBack(value);
        return true;
    }

    Node *prevNode = getNodeAt(index - 1);
    if (prevNode == nullptr) {
        return false;
    }

    Node *newNode = new Node(value);
    newNode->m_next = prevNode->m_next;
    newNode->m_prev = prevNode;

    if (prevNode->m_next != nullptr) {
        prevNode->m_next->m_prev = newNode;
    }
    prevNode->m_next = newNode;

    ++m_size;
    return true;
}

// 删除节点：先找到目标节点，再改链并 delete。
template<typename T>
bool DoubleLinkedList<T>::removeAt(std::size_t index) {
    if (index >= m_size) {
        return false;
    }

    if (index == 0) {
        Node *oldHead = m_head;
        m_head = m_head->m_next;

        if (m_head != nullptr) {
            m_head->m_prev = nullptr;
        } else {
            m_tail = nullptr;
        }

        delete oldHead;
        --m_size;
        return true;
    }

    Node *targetNode = getNodeAt(index);
    if (targetNode == nullptr) {
        return false;
    }
    if (targetNode->m_prev != nullptr) {
        targetNode->m_prev->m_next = targetNode->m_next;
    }
    if (targetNode->m_next != nullptr) {
        targetNode->m_next->m_prev = targetNode->m_prev;
    } else {
        m_tail = targetNode->m_prev;
    }
    delete targetNode;
    --m_size;
    return true;
}

// getAt 不暴露内部节点，只返回值。
template<typename T>
bool DoubleLinkedList<T>::getAt(const std::size_t index, T &outValue) const {
    const Node *node = getNodeAt(index);
    if (node == nullptr) {
        return false;
    }

    outValue = node->m_value;
    return true;
}

// setAt 直接定位后覆盖节点值。
template<typename T>
bool DoubleLinkedList<T>::setAt(const std::size_t index, const T &value) {
    Node *node = getNodeAt(index);
    if (node == nullptr) {
        return false;
    }

    node->m_value = value;
    return true;
}

// 逐节点 delete，避免内存泄漏。
template<typename T>
void DoubleLinkedList<T>::clear() {
    Node *current = m_head;
    while (current != nullptr) {
        Node *next = current->m_next;
        delete current;
        current = next;
    }

    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

// O(1)：直接返回记录的节点数量。
template<typename T>
std::size_t DoubleLinkedList<T>::size() const {
    return m_size;
}

// O(1)：空表判定。
template<typename T>
bool DoubleLinkedList<T>::isEmpty() const {
    return m_size == 0;
}

//---------------------------内部工具函数----------------------------
// getNodeAt：根据 index 定位节点，越界返回 nullptr。
template<typename T>
typename DoubleLinkedList<T>::Node *DoubleLinkedList<T>::getNodeAt(const std::size_t index) {
    if (index >= m_size) {
        return nullptr;
    }

    Node *current = m_head;
    for (std::size_t i = 0; i < index; ++i) {
        current = current->m_next;
    }
    return current;
}

template<typename T>
const typename DoubleLinkedList<T>::Node *DoubleLinkedList<T>::getNodeAt(const std::size_t index) const {
    if (index >= m_size) {
        return nullptr;
    }

    const Node *current = m_head;
    for (std::size_t i = 0; i < index; ++i) {
        current = current->m_next;
    }
    return current;
}

// copyFrom：逐节点复制 other，保证深拷贝。
template<typename T>
void DoubleLinkedList<T>::copyFrom(const DoubleLinkedList &other) {
    Node *current = other.m_head;
    while (current != nullptr) {
        pushBack(current->m_value);
        current = current->m_next;
    }
}

// moveFrom：直接接管 other 的内部指针，避免 O(n) 拷贝。
template<typename T>
void DoubleLinkedList<T>::moveFrom(DoubleLinkedList &other) noexcept {
    m_head = other.m_head;
    m_tail = other.m_tail;
    m_size = other.m_size;

    // 把源链表置空，保证其析构安全。
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;
}


