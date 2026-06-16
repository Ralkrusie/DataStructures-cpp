#pragma once

#include <cstddef>
#include <iostream>
#include <type_traits>

template <typename T>
class mySeqDoublyList {
public:
	mySeqDoublyList() : data(nullptr), size(0), capacity(0) {
		reserve(8);
	}

	explicit mySeqDoublyList(size_t initialCapacity) : data(nullptr), size(0), capacity(0) {
		reserve(initialCapacity == 0 ? 1 : initialCapacity);
	}

	~mySeqDoublyList() {
		delete[] data;
	}

	mySeqDoublyList(const mySeqDoublyList &) = delete;
	mySeqDoublyList &operator=(const mySeqDoublyList &) = delete;

	void pushFront(const T &x) {
		ensureCapacity(size + 1);
		for (size_t i = size; i > 0; --i) {
			data[i] = data[i - 1];
		}
		data[0] = x;
		++size;
	}

	void pushBack(const T &x) {
		ensureCapacity(size + 1);
		data[size] = x;
		++size;
	}

	void popFront() {
		if (isEmpty()) {
			return;
		}
		for (size_t i = 1; i < size; ++i) {
			data[i - 1] = data[i];
		}
		--size;
	}

	void popBack() {
		if (isEmpty()) {
			return;
		}
		--size;
	}

	// Insert before the k-th element (1-based).
	bool insertAt(int k, const T &x) {
		if (k < 1 || static_cast<size_t>(k) > size + 1) {
			return false;
		}
		size_t idx = static_cast<size_t>(k - 1);
		ensureCapacity(size + 1);
		for (size_t i = size; i > idx; --i) {
			data[i] = data[i - 1];
		}
		data[idx] = x;
		++size;
		return true;
	}

	// Delete the k-th element (1-based).
	bool deleteAt(int k) {
		if (k < 1 || static_cast<size_t>(k) > size) {
			return false;
		}
		size_t idx = static_cast<size_t>(k - 1);
		for (size_t i = idx + 1; i < size; ++i) {
			data[i - 1] = data[i];
		}
		--size;
		return true;
	}

	T front() const {
		if (isEmpty()) {
			return T();
		}
		return data[0];
	}

	T back() const {
		if (isEmpty()) {
			return T();
		}
		return data[size - 1];
	}

	T at(size_t index) const {
		if (index >= size) {
			return T();
		}
		return data[index];
	}

	// indexFromBack = 0 means the last element.
	T atFromBack(size_t indexFromBack) const {
		if (indexFromBack >= size) {
			return T();
		}
		return data[size - 1 - indexFromBack];
	}

	// Returns first position (1-based), or -1 if not found.
	int findFirst(const T &x) const {
		for (size_t i = 0; i < size; ++i) {
			if (data[i] == x) {
				return static_cast<int>(i) + 1;
			}
		}
		return -1;
	}

	void clear() {
		size = 0;
	}

	bool isEmpty() const {
		return size == 0;
	}

	size_t getSize() const {
		return size;
	}

	void displayForward() const {
		if (size > 0) {
			std::cout << data[0];
			for (size_t i = 1; i < size; ++i) {
				std::cout << ' ' << data[i];
			}
		}
		std::cout << '\n';
	}

	void displayBackward() const {
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
		displayForward();
	}

	template <typename U = T, typename std::enable_if<std::is_integral<U>::value, int>::type = 0>
	void createList(int n) {
		clear();
		for (int i = 1; i <= n; ++i) {
			pushBack(static_cast<T>(i));
		}
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
