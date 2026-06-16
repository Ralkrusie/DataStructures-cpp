#pragma once

#include <cstddef>
#include <iostream>

template <typename T>
class mySeqStack {
public:
	mySeqStack() : data(nullptr), size(0), capacity(0) {
		reserve(8);
	}

	explicit mySeqStack(size_t initialCapacity) : data(nullptr), size(0), capacity(0) {
		reserve(initialCapacity == 0 ? 1 : initialCapacity);
	}

	~mySeqStack() {
		delete[] data;
	}

	mySeqStack(const mySeqStack &) = delete;
	mySeqStack &operator=(const mySeqStack &) = delete;

	void push(const T &x) {
		ensureCapacity(size + 1);
		data[size] = x;
		++size;
	}

	void pop() {
		if (isEmpty()) {
			return;
		}
		--size;
	}

	T top() const {
		if (isEmpty()) {
			return T();
		}
		return data[size - 1];
	}

	bool isEmpty() const {
		return size == 0;
	}

	size_t getSize() const {
		return size;
	}

	void clear() {
		size = 0;
	}

	void display() const {
		if (size > 0) {
			std::cout << data[size - 1];
			for (size_t i = size - 1; i > 0; --i) {
				std::cout << ' ' << data[i - 1];
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

	void reverse() {
		if (size <= 1) {
			return;
		}
		for (size_t left = 0, right = size - 1; left < right; ++left, --right) {
			T tmp = data[left];
			data[left] = data[right];
			data[right] = tmp;
		}
	}

	T at(size_t index) const {
		if (index >= size) {
			return T();
		}
		// 与链式栈保持一致：index=0 表示栈顶。
		return data[size - 1 - index];
	}

	// 删除从栈顶开始的第 index 个元素（0 下标）。
	void popAt(size_t indexFromTop) {
		if (indexFromTop >= size) {
			return;
		}
		size_t index = size - 1 - indexFromTop;
		for (size_t i = index + 1; i < size; ++i) {
			data[i - 1] = data[i];
		}
		--size;
	}

private:
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
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
		capacity = newCapacity;
	}

	T *data;
	size_t size;
	size_t capacity;
};
