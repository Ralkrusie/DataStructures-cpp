#pragma once

#include <cstddef>
#include <iostream>

class mySeqString {
public:
	mySeqString() : data(nullptr), size(0), capacity(0) {
		reserve(8);
	}

	explicit mySeqString(size_t initialCapacity) : data(nullptr), size(0), capacity(0) {
		reserve(initialCapacity == 0 ? 1 : initialCapacity);
	}

	explicit mySeqString(const char *cstr) : data(nullptr), size(0), capacity(0) {
		reserve(8);
		assign(cstr);
	}

	~mySeqString() {
		delete[] data;
	}

	mySeqString(const mySeqString &) = delete;
	mySeqString &operator=(const mySeqString &) = delete;

	void pushBack(char ch) {
		ensureCapacity(size + 1);
		data[size] = ch;
		++size;
	}

	// 在第 k 个位置前插入字符（1 下标）；非法位置返回 false。
	bool insertAt(int k, char ch) {
		if (k < 1 || static_cast<size_t>(k) > size + 1) {
			return false;
		}
		size_t idx = static_cast<size_t>(k - 1);
		ensureCapacity(size + 1);
		for (size_t i = size; i > idx; --i) {
			data[i] = data[i - 1];
		}
		data[idx] = ch;
		++size;
		return true;
	}

	// 删除第 k 个字符（1 下标）；非法位置返回 false。
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

	// 返回第一次出现的位置（1 下标），不存在返回 -1。
	int findFirst(char ch) const {
		for (size_t i = 0; i < size; ++i) {
			if (data[i] == ch) {
				return static_cast<int>(i) + 1;
			}
		}
		return -1;
	}

	char at(size_t index) const {
		if (index >= size) {
			return '\0';
		}
		return data[index];
	}

	void concat(const mySeqString &other) {
		ensureCapacity(size + other.size);
		for (size_t i = 0; i < other.size; ++i) {
			data[size + i] = other.data[i];
		}
		size += other.size;
	}

	void append(const char *cstr) {
		if (cstr == nullptr) {
			return;
		}
		while (*cstr != '\0') {
			pushBack(*cstr);
			++cstr;
		}
	}

	void assign(const char *cstr) {
		clear();
		append(cstr);
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

	void display() const {
		for (size_t i = 0; i < size; ++i) {
			std::cout << data[i];
		}
		std::cout << '\n';
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
		char *newData = new char[newCapacity];
		for (size_t i = 0; i < size; ++i) {
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
		capacity = newCapacity;
	}

	char *data;
	size_t size;
	size_t capacity;
};
