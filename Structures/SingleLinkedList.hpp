#ifndef DATASTRUCTURE_SINGLELINKEDLIST_H
#define DATASTRUCTURE_SINGLELINKEDLIST_H

#include <cstddef> // for std::size_t
#include <utility> // for std::move

// 单链表模板：用 T 表示节点里存储的数据类型。
// 适合刚开始学习 STL/数据结构时，理解“节点 + 指针连接”的底层模型。

//---------------------------声明----------------------------
template<typename T>
class SingleLinkedList {
public:
	// 基本生命周期：遵循“规则五（Rule of Five）”，避免浅拷贝导致重复释放。
	SingleLinkedList();
	SingleLinkedList(const SingleLinkedList &other);
	SingleLinkedList &operator=(const SingleLinkedList &other);
	SingleLinkedList(SingleLinkedList &&other) noexcept;
	SingleLinkedList &operator=(SingleLinkedList &&other) noexcept;
	~SingleLinkedList();

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
	// 链表节点：保存数据和指向下一个节点的指针。
	struct Node {
		T m_value;
		Node *m_next;

		explicit Node(const T &value) : m_value(value), m_next(nullptr) {
		}
	};

	Node *m_head;
	Node *m_tail;
	std::size_t m_size;

	[[nodiscard]] Node *getNodeAt(std::size_t index);
	[[nodiscard]] const Node *getNodeAt(std::size_t index) const;
	// 深拷贝/资源接管的内部工具函数。
	void copyFrom(const SingleLinkedList &other);
	void moveFrom(SingleLinkedList &other) noexcept;
};


//---------------------------定义----------------------------
// 默认构造：空链表状态。
template<typename T>
SingleLinkedList<T>::SingleLinkedList() : m_head(nullptr), m_tail(nullptr), m_size(0) {
}

// 拷贝构造：逐个节点复制，保证两个链表互不影响。
template<typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList &other) : SingleLinkedList() {
	copyFrom(other);
}

// 拷贝赋值：先清空自身，再深拷贝。
template<typename T>
SingleLinkedList<T> &SingleLinkedList<T>::operator=(const SingleLinkedList &other) {
	if (this == &other) {
		return *this;
	}

	clear();
	copyFrom(other);
	return *this;
}

// 移动构造：直接接管 other 的内部指针，避免 O(n) 拷贝。
//noexcept 保证移动操作不会抛异常，符合移动语义要求。
template<typename T>
SingleLinkedList<T>::SingleLinkedList(SingleLinkedList &&other) noexcept : SingleLinkedList() {
	moveFrom(other);
}

// 移动赋值：先释放自身，再接管 other 资源。
template<typename T>
SingleLinkedList<T> &SingleLinkedList<T>::operator=(SingleLinkedList &&other) noexcept {
	if (this == &other) {
		return *this;
	}

	clear();
	moveFrom(other);
	return *this;
}

// 析构时统一走 clear，确保节点不会泄漏。
template<typename T>
SingleLinkedList<T>::~SingleLinkedList() {
	clear();
}

// 头插：新节点 next 指向原头节点，再更新头指针。
template<typename T>
void SingleLinkedList<T>::pushFront(const T &value) {
	Node *newNode = new Node(value);
	newNode->m_next = m_head;
	m_head = newNode;

	if (m_tail == nullptr) {
		m_tail = newNode;
	}

	++m_size;
}

// 尾插：维护 m_tail，避免每次从头遍历到尾部。
template<typename T>
void SingleLinkedList<T>::pushBack(const T &value) {
	Node *newNode = new Node(value);

	if (m_tail == nullptr) {
		m_head = newNode;
		m_tail = newNode;
	} else {
		m_tail->m_next = newNode;
		m_tail = newNode;
	}

	++m_size;
}

// 在任意位置插入：核心是先找到前驱节点，再改链。
template<typename T>
bool SingleLinkedList<T>::insertAt(std::size_t index, const T &value) {
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
	prevNode->m_next = newNode;
	++m_size;
	return true;
}

// 删除任意位置节点：需要特别处理删除头节点和尾节点。
template<typename T>
bool SingleLinkedList<T>::removeAt(std::size_t index) {
	if (index >= m_size) {
		return false;
	}

	if (index == 0) {
		const Node *oldHead = m_head;
		m_head = m_head->m_next;
		delete oldHead;
		--m_size;

		if (m_size == 0) {
			m_tail = nullptr;
		}

		return true;
	}

	Node *prevNode = getNodeAt(index - 1);
	if (prevNode == nullptr || prevNode->m_next == nullptr) {
		return false;
	}

	Node *targetNode = prevNode->m_next;
	prevNode->m_next = targetNode->m_next;

	if (targetNode == m_tail) {
		m_tail = prevNode;
	}

	delete targetNode;
	--m_size;
	return true;
}

// getAt 不暴露内部节点，只返回值。
template<typename T>
bool SingleLinkedList<T>::getAt(const std::size_t index, T &outValue) const {
	const Node *node = getNodeAt(index);
	if (node == nullptr) {
		return false;
	}

	outValue = node->m_value;
	return true;
}

// setAt 直接定位后覆盖节点值。
template<typename T>
bool SingleLinkedList<T>::setAt(const std::size_t index, const T &value) {
	Node *node = getNodeAt(index);
	if (node == nullptr) {
		return false;
	}

	node->m_value = value;
	return true;
}

// 逐节点 delete，避免内存泄漏。
template<typename T>
void SingleLinkedList<T>::clear() {
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
std::size_t SingleLinkedList<T>::size() const {
	return m_size;
}

// O(1)：空表判定。
template<typename T>
bool SingleLinkedList<T>::isEmpty() const {
	return m_size == 0;
}

// 非 const 版本：给可修改操作使用（如 setAt / removeAt）。
template<typename T>
typename SingleLinkedList<T>::Node *SingleLinkedList<T>::getNodeAt(const std::size_t index) {
	if (index >= m_size) {
		return nullptr;
	}

	Node *current = m_head;
	for (std::size_t i = 0; i < index; ++i) {
		current = current->m_next;
	}

	return current;
}

// const 版本：给只读操作使用（如 getAt）。
template<typename T>
const typename SingleLinkedList<T>::Node *SingleLinkedList<T>::getNodeAt(const std::size_t index) const {
	if (index >= m_size) {
		return nullptr;
	}

	Node *current = m_head;
	for (std::size_t i = 0; i < index; ++i) {
		current = current->m_next;
	}

	return current;
}

// 深拷贝：按原链表顺序依次尾插。
template<typename T>
void SingleLinkedList<T>::copyFrom(const SingleLinkedList &other) {
	Node *current = other.m_head;
	while (current != nullptr) {
		pushBack(current->m_value);
		current = current->m_next;
	}
}

// 资源转移后，把源链表置空，保证其析构安全。
template<typename T>
void SingleLinkedList<T>::moveFrom(SingleLinkedList &other) noexcept {
	m_head = other.m_head;
	m_tail = other.m_tail;
	m_size = other.m_size;

	other.m_head = nullptr;
	other.m_tail = nullptr;
	other.m_size = 0;
}

#endif //DATASTRUCTURE_SINGLELINKEDLIST_H