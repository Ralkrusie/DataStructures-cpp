#pragma once

#include <cstddef>
#include <iostream>

template <typename T>
class mySeqDeque {
public:
	mySeqDeque() : data(nullptr), head(0), size(0), capacity(0) {
		reserve(8);
	}

	explicit mySeqDeque(size_t initialCapacity) : data(nullptr), head(0), size(0), capacity(0) {
		reserve(initialCapacity == 0 ? 1 : initialCapacity);
	}

	~mySeqDeque() {
		delete[] data;
	}

	mySeqDeque(const mySeqDeque &) = delete;
	mySeqDeque &operator=(const mySeqDeque &) = delete;

	void pushFront(const T &x) {
		ensureCapacity(size + 1);
		head = (head + capacity - 1) % capacity;
		data[head] = x;
		++size;
	}

	void pushBack(const T &x) {
		ensureCapacity(size + 1);
		data[index(size)] = x;
		++size;
	}

	void popFront() {
		if (isEmpty()) {
			return;
		}
		head = (head + 1) % capacity;
		--size;
		if (size == 0) {
			head = 0;
		}
	}

	void popBack() {
		if (isEmpty()) {
			return;
		}
		--size;
		if (size == 0) {
			head = 0;
		}
	}

	T front() const {
		if (isEmpty()) {
			return T();
		}
		return data[index(0)];
	}

	T back() const {
		if (isEmpty()) {
			return T();
		}
		return data[index(size - 1)];
	}

	bool isEmpty() const {
		return size == 0;
	}

	size_t getSize() const {
		return size;
	}

	void clear() {
		head = 0;
		size = 0;
	}

	void display() const {
		if (!isEmpty()) {
			std::cout << data[index(0)];
			for (size_t i = 1; i < size; ++i) {
				std::cout << ' ' << data[index(i)];
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
	size_t index(size_t offset) const {
		return (head + offset) % capacity;
	}

	void ensureCapacity(size_t wanted) {
		if (wanted <= capacity) {
			return;
		}
		size_t newCapacity = (capacity == 0 ? 1 : capacity);
		while (newCapacity < wanted) {
			newCapacity *= 2;
		}
		reserve(newCapacity);
	}

	void reserve(size_t newCapacity) {
		if (newCapacity <= capacity) {
			return;
		}
		T *newData = new T[newCapacity];
		for (size_t i = 0; i < size; ++i) {
			newData[i] = data[(head + i) % (capacity == 0 ? 1 : capacity)];
		}
		delete[] data;
		data = newData;
		capacity = newCapacity;
		head = 0;
	}

	T *data;
	size_t head;
	size_t size;
	size_t capacity;
};
