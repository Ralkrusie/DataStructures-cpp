#pragma once

#include <cstddef>
#include <iostream>
#include <queue>

template <typename T>
class mySeqBinaryTree {
public:
	mySeqBinaryTree() : data(nullptr), used(nullptr), size(0), capacity(0), maxIndex(0) {
		reserve(16);
	}

	explicit mySeqBinaryTree(size_t initialCapacity)
		: data(nullptr), used(nullptr), size(0), capacity(0), maxIndex(0) {
		reserve(initialCapacity < 2 ? 2 : initialCapacity);
	}

	~mySeqBinaryTree() {
		delete[] data;
		delete[] used;
	}

	mySeqBinaryTree(const mySeqBinaryTree &) = delete;
	mySeqBinaryTree &operator=(const mySeqBinaryTree &) = delete;

	void clear() {
		for (size_t i = 1; i <= maxIndex; ++i) {
			used[i] = false;
		}
		size = 0;
		maxIndex = 0;
	}

	bool isEmpty() const {
		return size == 0;
	}

	size_t getSize() const {
		return size;
	}

	size_t height() const {
		return height(1);
	}

	void setRoot(const T &x) {
		clear();
		used[1] = true;
		data[1] = x;
		size = 1;
		maxIndex = 1;
	}

	T getRoot() const {
		if (isEmpty()) {
			return T();
		}
		return data[1];
	}

	bool contains(const T &x) const {
		return findIndex(1, x) != 0;
	}

	void insertLeft(const T &parent, const T &x) {
		size_t parentIndex = findIndex(1, parent);
		if (parentIndex == 0) {
			return;
		}
		size_t childIndex = parentIndex * 2;
		ensureIndex(childIndex);
		if (used[childIndex]) {
			return;
		}
		used[childIndex] = true;
		data[childIndex] = x;
		++size;
		if (childIndex > maxIndex) {
			maxIndex = childIndex;
		}
	}

	void insertRight(const T &parent, const T &x) {
		size_t parentIndex = findIndex(1, parent);
		if (parentIndex == 0) {
			return;
		}
		size_t childIndex = parentIndex * 2 + 1;
		ensureIndex(childIndex);
		if (used[childIndex]) {
			return;
		}
		used[childIndex] = true;
		data[childIndex] = x;
		++size;
		if (childIndex > maxIndex) {
			maxIndex = childIndex;
		}
	}

	void display() const {
		displayLevelOrder();
	}

	void displayPreOrder() const {
		bool first = true;
		displayPreOrder(1, first);
		std::cout << '\n';
	}

	void displayInOrder() const {
		bool first = true;
		displayInOrder(1, first);
		std::cout << '\n';
	}

	void displayPostOrder() const {
		bool first = true;
		displayPostOrder(1, first);
		std::cout << '\n';
	}

	void displayLevelOrder() const {
		std::queue<size_t> nodeQueue;
		if (!isEmpty()) {
			nodeQueue.push(1);
		}
		bool first = true;
		while (!nodeQueue.empty()) {
			size_t current = nodeQueue.front();
			nodeQueue.pop();
			if (!isValidIndex(current) || !used[current]) {
				continue;
			}
			displayValue(data[current], first);
			size_t leftIndex = current * 2;
			size_t rightIndex = leftIndex + 1;
			if (isValidIndex(leftIndex) && used[leftIndex]) {
				nodeQueue.push(leftIndex);
			}
			if (isValidIndex(rightIndex) && used[rightIndex]) {
				nodeQueue.push(rightIndex);
			}
		}
		std::cout << '\n';
	}

	void displayEmpty() const {
		if (isEmpty()) {
			std::cout << "EMPTY\n";
			return;
		}
		display();
	}

private:
	bool isValidIndex(size_t index) const {
		return index < capacity;
	}

	void ensureIndex(size_t index) {
		if (index < capacity) {
			return;
		}
		size_t newCapacity = (capacity == 0 ? 2 : capacity);
		while (newCapacity <= index) {
			newCapacity *= 2;
		}
		reserve(newCapacity);
	}

	void reserve(size_t newCapacity) {
		if (newCapacity <= capacity) {
			return;
		}
		T *newData = new T[newCapacity];
		bool *newUsed = new bool[newCapacity];
		for (size_t i = 0; i < newCapacity; ++i) {
			newUsed[i] = false;
		}
		for (size_t i = 1; i <= maxIndex && i < newCapacity; ++i) {
			if (used != nullptr && used[i]) {
				newData[i] = data[i];
				newUsed[i] = true;
			}
		}
		delete[] data;
		delete[] used;
		data = newData;
		used = newUsed;
		capacity = newCapacity;
	}

	size_t findIndex(size_t currentIndex, const T &x) const {
		if (!isValidIndex(currentIndex) || !used[currentIndex]) {
			return 0;
		}
		if (data[currentIndex] == x) {
			return currentIndex;
		}
		size_t found = findIndex(currentIndex * 2, x);
		if (found != 0) {
			return found;
		}
		return findIndex(currentIndex * 2 + 1, x);
	}

	size_t height(size_t currentIndex) const {
		if (!isValidIndex(currentIndex) || !used[currentIndex]) {
			return 0;
		}
		size_t leftHeight = height(currentIndex * 2);
		size_t rightHeight = height(currentIndex * 2 + 1);
		return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
	}

	static void displayValue(const T &x, bool &first) {
		if (first) {
			std::cout << x;
			first = false;
		} else {
			std::cout << ' ' << x;
		}
	}

	void displayPreOrder(size_t currentIndex, bool &first) const {
		if (!isValidIndex(currentIndex) || !used[currentIndex]) {
			return;
		}
		displayValue(data[currentIndex], first);
		displayPreOrder(currentIndex * 2, first);
		displayPreOrder(currentIndex * 2 + 1, first);
	}

	void displayInOrder(size_t currentIndex, bool &first) const {
		if (!isValidIndex(currentIndex) || !used[currentIndex]) {
			return;
		}
		displayInOrder(currentIndex * 2, first);
		displayValue(data[currentIndex], first);
		displayInOrder(currentIndex * 2 + 1, first);
	}

	void displayPostOrder(size_t currentIndex, bool &first) const {
		if (!isValidIndex(currentIndex) || !used[currentIndex]) {
			return;
		}
		displayPostOrder(currentIndex * 2, first);
		displayPostOrder(currentIndex * 2 + 1, first);
		displayValue(data[currentIndex], first);
	}

	T *data;
	bool *used;
	size_t size;
	size_t capacity;
	size_t maxIndex;
};