/*
判断两树是否相同
*/

#include <climits>
#include <cstddef>
#include <cctype>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <string>
#include <vector>
namespace et {
	struct BinaryNode {
		int value;
		BinaryNode *left;
		BinaryNode *right;

		
		explicit BinaryNode(int v) : value(v), left(nullptr), right(nullptr) {}
	};

	inline BinaryNode *buildPreorder(const std::vector<int> &values, size_t &index, int nullValue = -1) {
		if (index >= values.size() || values[index] == nullValue) {
			++index;
			return nullptr;
		}
		BinaryNode *node = new BinaryNode(values[index++]);
		node->left = buildPreorder(values, index, nullValue);
		node->right = buildPreorder(values, index, nullValue);
		return node;
	}

	inline BinaryNode *buildPreorder(const std::vector<int> &values, int nullValue = -1) {
		size_t index = 0;
		return buildPreorder(values, index, nullValue);
	}

	inline void destroy(BinaryNode *node) {
		if (node == nullptr) {
			return;
		}
		destroy(node->left);
		destroy(node->right);
		delete node;
	}

	inline bool sameTree(BinaryNode *left, BinaryNode *right) {
		if (left == nullptr || right == nullptr) {
			return left == right;
		}
		return left->value == right->value
			&& sameTree(left->left, right->left)
			&& sameTree(left->right, right->right);
	}
}



static std::vector<int> parseLineInts(const std::string &line) {
	std::vector<int> values;
	std::stringstream ss(line);
	int x;
	while (ss >> x) {
		values.push_back(x);
	}
	return values;
}

int main() {
	std::string line1;
	std::string line2;
	while (line1.empty() && std::getline(std::cin, line1)) {
	}
	while (line2.empty() && std::getline(std::cin, line2)) {
	}
	et::BinaryNode *firstTree = et::buildPreorder(parseLineInts(line1));
	et::BinaryNode *secondTree = et::buildPreorder(parseLineInts(line2));
	std::cout << (et::sameTree(firstTree, secondTree) ? "YES" : "NO") << '\n';
	et::destroy(firstTree);
	et::destroy(secondTree);
	return 0;
}