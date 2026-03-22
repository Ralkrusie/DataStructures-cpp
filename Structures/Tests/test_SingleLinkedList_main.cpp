#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "SingleLinkedList.hpp"

template<typename T>
std::vector<T> toVector(const SingleLinkedList<T> &list) {
	std::vector<T> values;
	values.reserve(list.size());

	for (std::size_t i = 0; i < list.size(); ++i) {
		T value{};
		const bool ok = list.getAt(i, value);
		assert(ok);
		values.push_back(value);
	}

	return values;
}

void testBasicPushAndAccess() {
	SingleLinkedList<int> list;
	assert(list.isEmpty());
	assert(list.size() == 0);

	list.pushBack(1);
	list.pushBack(2);
	list.pushFront(0);

	assert(!list.isEmpty());
	assert(list.size() == 3);
	assert((toVector(list) == std::vector<int>{0, 1, 2}));

	int out = -1;
	assert(list.getAt(1, out));
	assert(out == 1);
	assert(!list.getAt(99, out));
}

void testInsertSetAndRemove() {
	SingleLinkedList<int> list;
	list.pushBack(1);
	list.pushBack(3);

	assert(list.insertAt(1, 2));
	assert(list.insertAt(3, 4));
	assert(list.insertAt(0, 0));
	assert(!list.insertAt(6, 100));
	assert((toVector(list) == std::vector<int>{0, 1, 2, 3, 4}));

	assert(list.setAt(2, 20));
	assert(!list.setAt(100, 7));
	assert((toVector(list) == std::vector<int>{0, 1, 20, 3, 4}));

	assert(list.removeAt(0));
	assert(list.removeAt(1));
	assert(list.removeAt(2));
	assert(!list.removeAt(10));
	assert((toVector(list) == std::vector<int>{1, 3}));
}

void testCopyAndMoveSemantics() {
	SingleLinkedList<std::string> original;
	original.pushBack("A");
	original.pushBack("B");
	original.pushBack("C");

	SingleLinkedList<std::string> copied(original);
	assert((toVector(copied) == std::vector<std::string>{"A", "B", "C"}));

	original.setAt(1, "X");
	assert((toVector(original) == std::vector<std::string>{"A", "X", "C"}));
	assert((toVector(copied) == std::vector<std::string>{"A", "B", "C"}));

	SingleLinkedList<std::string> assigned;
	assigned.pushBack("tmp");
	assigned = copied;
	assert((toVector(assigned) == std::vector<std::string>{"A", "B", "C"}));

	SingleLinkedList<std::string> moved(std::move(copied));
	assert((toVector(moved) == std::vector<std::string>{"A", "B", "C"}));
	assert(copied.isEmpty());

	SingleLinkedList<std::string> moveAssigned;
	moveAssigned.pushBack("old");
	moveAssigned = std::move(assigned);
	assert((toVector(moveAssigned) == std::vector<std::string>{"A", "B", "C"}));
	assert(assigned.isEmpty());
}

void testClear() {
	SingleLinkedList<int> list;
	list.pushBack(10);
	list.pushBack(20);
	list.clear();

	assert(list.isEmpty());
	assert(list.size() == 0);

	int out = 0;
	assert(!list.getAt(0, out));
}

void testStablePartitionLessThan() {
	SingleLinkedList<int> list;
	for (int value: {5, 1, 4, 2, 3, 2}) {
		list.pushBack(value);
	}

	list.stablePartitionLessThan(3);
	assert((toVector(list) == std::vector<int>{1, 2, 2, 5, 4, 3}));
	assert(list.size() == 6);

	SingleLinkedList<int> allLess;
	for (int value: {1, 0, -1}) {
		allLess.pushBack(value);
	}
	allLess.stablePartitionLessThan(10);
	assert((toVector(allLess) == std::vector<int>{1, 0, -1}));

	SingleLinkedList<int> allGreaterEqual;
	for (int value: {7, 8, 9}) {
		allGreaterEqual.pushBack(value);
	}
	allGreaterEqual.stablePartitionLessThan(3);
	assert((toVector(allGreaterEqual) == std::vector<int>{7, 8, 9}));

	SingleLinkedList<int> empty;
	empty.stablePartitionLessThan(42);
	assert(empty.isEmpty());

	SingleLinkedList<int> single;
	single.pushBack(5);
	single.stablePartitionLessThan(6);
	assert((toVector(single) == std::vector<int>{5}));
}

int main() {
	testBasicPushAndAccess();
	testInsertSetAndRemove();
	testCopyAndMoveSemantics();
	testClear();
	testStablePartitionLessThan();

	std::cout << "All SingleLinkedList tests passed.\n";
	return 0;
}
