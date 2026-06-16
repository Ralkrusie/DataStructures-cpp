#pragma once

#include <cstddef>

template <typename T>
class mySeqList {
public:
	mySeqList() : data(nullptr), size(0), capacity(0) {
		reserve(8);
	}

	explicit mySeqList(size_t initialCapacity) : data(nullptr), size(0), capacity(0) {
		reserve(initialCapacity == 0 ? 1 : initialCapacity);
	}

	~mySeqList() {
		delete[] data;
	}

	mySeqList(const mySeqList &) = delete;
	mySeqList &operator=(const mySeqList &) = delete;

	void pushBack(const T &x) {
		ensureCapacity(size + 1);
		data[size] = x;
		++size;
	}

	// 在第 k 个位置前插入（1 下标）；非法位置返回 false。
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

	// 删除第 k 个元素（1 下标）；非法位置返回 false。
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
	int findFirst(const T &x) const {
		for (size_t i = 0; i < size; ++i) {
			if (data[i] == x) {
				return static_cast<int>(i) + 1;
			}
		}
		return -1;
	}

	T at(size_t index) const {
		if (index >= size) {
			return T();
		}
		return data[index];
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
