#pragma once

#include <climits>
#include <cstddef>
#include <cctype>
#include <iostream>
#include <queue>
#include <sstream>
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

	inline bool contains(BinaryNode *node, int target) {
		if (node == nullptr) {
			return false;
		}
		if (node->value == target) {
			return true;
		}
		return contains(node->left, target) || contains(node->right, target);
	}

	inline bool isMirror(BinaryNode *left, BinaryNode *right) {
		if (left == nullptr || right == nullptr) {
			return left == right;
		}
		if (left->value != right->value) {
			return false;
		}
		return isMirror(left->left, right->right) && isMirror(left->right, right->left);
	}

	inline bool isSymmetric(BinaryNode *root) {
		return root == nullptr || isMirror(root->left, root->right);
	}

	inline bool sameTree(BinaryNode *left, BinaryNode *right) {
		if (left == nullptr || right == nullptr) {
			return left == right;
		}
		return left->value == right->value
			&& sameTree(left->left, right->left)
			&& sameTree(left->right, right->right);
	}

	inline void mirror(BinaryNode *node) {
		if (node == nullptr) {
			return;
		}
		BinaryNode *tmp = node->left;
		node->left = node->right;
		node->right = tmp;
		mirror(node->left);
		mirror(node->right);
	}

	inline size_t height(BinaryNode *node) {
		if (node == nullptr) {
			return 0;
		}
		size_t leftHeight = height(node->left);
		size_t rightHeight = height(node->right);
		return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
	}

	inline size_t countNodes(BinaryNode *node) {
		if (node == nullptr) {
			return 0;
		}
		return 1 + countNodes(node->left) + countNodes(node->right);
	}

	inline size_t countLeaves(BinaryNode *node) {
		if (node == nullptr) {
			return 0;
		}
		if (node->left == nullptr && node->right == nullptr) {
			return 1;
		}
		return countLeaves(node->left) + countLeaves(node->right);
	}

	inline void preorder(BinaryNode *node, bool &first) {
		if (node == nullptr) {
			return;
		}
		if (!first) {
			std::cout << ' ';
		}
		std::cout << node->value;
		first = false;
		preorder(node->left, first);
		preorder(node->right, first);
	}

	inline void inorder(BinaryNode *node, bool &first) {
		if (node == nullptr) {
			return;
		}
		inorder(node->left, first);
		if (!first) {
			std::cout << ' ';
		}
		std::cout << node->value;
		first = false;
		inorder(node->right, first);
	}

	inline void postorder(BinaryNode *node, bool &first) {
		if (node == nullptr) {
			return;
		}
		postorder(node->left, first);
		postorder(node->right, first);
		if (!first) {
			std::cout << ' ';
		}
		std::cout << node->value;
		first = false;
	}

	inline void levelorder(BinaryNode *root) {
		std::queue<BinaryNode *> nodeQueue;
		if (root != nullptr) {
			nodeQueue.push(root);
		}
		bool first = true;
		while (!nodeQueue.empty()) {
			BinaryNode *current = nodeQueue.front();
			nodeQueue.pop();
			if (!first) {
				std::cout << ' ';
			}
			std::cout << current->value;
			first = false;
			if (current->left != nullptr) {
				nodeQueue.push(current->left);
			}
			if (current->right != nullptr) {
				nodeQueue.push(current->right);
			}
		}
		std::cout << '\n';
	}

	inline BinaryNode *lca(BinaryNode *node, int p, int q) {
		if (node == nullptr) {
			return nullptr;
		}
		if (node->value == p || node->value == q) {
			return node;
		}
		BinaryNode *left = lca(node->left, p, q);
		BinaryNode *right = lca(node->right, p, q);
		if (left != nullptr && right != nullptr) {
			return node;
		}
		return left != nullptr ? left : right;
	}

	inline BinaryNode *findMin(BinaryNode *node) {
		if (node == nullptr) {
			return nullptr;
		}
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	inline BinaryNode *findMax(BinaryNode *node) {
		if (node == nullptr) {
			return nullptr;
		}
		while (node->right != nullptr) {
			node = node->right;
		}
		return node;
	}

	inline BinaryNode *insertBST(BinaryNode *node, int value) {
		if (node == nullptr) {
			return new BinaryNode(value);
		}
		if (value < node->value) {
			node->left = insertBST(node->left, value);
		} else if (node->value < value) {
			node->right = insertBST(node->right, value);
		}
		return node;
	}

	inline BinaryNode *buildBSTFromPreorderSequence(const std::vector<int> &values, int nullValue = -1) {
		BinaryNode *root = nullptr;
		for (int value : values) {
			if (value != nullValue) {
				root = insertBST(root, value);
			}
		}
		return root;
	}

	inline BinaryNode *removeBST(BinaryNode *node, int value, bool &removed) {
		if (node == nullptr) {
			return nullptr;
		}
		if (value < node->value) {
			node->left = removeBST(node->left, value, removed);
			return node;
		}
		if (node->value < value) {
			node->right = removeBST(node->right, value, removed);
			return node;
		}

		removed = true;
		if (node->left == nullptr) {
			BinaryNode *right = node->right;
			delete node;
			return right;
		}
		if (node->right == nullptr) {
			BinaryNode *left = node->left;
			delete node;
			return left;
		}

		BinaryNode *successor = findMin(node->right);
		node->value = successor->value;
		bool ignored = false;
		node->right = removeBST(node->right, successor->value, ignored);
		return node;
	}

	inline bool isBST(BinaryNode *node, long long low, long long high) {
		if (node == nullptr) {
			return true;
		}
		if (node->value <= low || node->value >= high) {
			return false;
		}
		return isBST(node->left, low, node->value) && isBST(node->right, node->value, high);
	}

	inline BinaryNode *bstLca(BinaryNode *node, int p, int q) {
		while (node != nullptr) {
			if (p < node->value && q < node->value) {
				node = node->left;
			} else if (p > node->value && q > node->value) {
				node = node->right;
			} else {
				return node;
			}
		}
		return nullptr;
	}

	inline BinaryNode *findBST(BinaryNode *node, int target) {
		while (node != nullptr) {
			if (target < node->value) {
				node = node->left;
			} else if (node->value < target) {
				node = node->right;
			} else {
				return node;
			}
		}
		return nullptr;
	}

	inline bool containsBST(BinaryNode *node, int target) {
		return findBST(node, target) != nullptr;
	}

	inline void collectInorder(BinaryNode *node, std::vector<int> &values) {
		if (node == nullptr) {
			return;
		}
		collectInorder(node->left, values);
		values.push_back(node->value);
		collectInorder(node->right, values);
	}

	inline bool kthSmallest(BinaryNode *node, size_t k, size_t &count, int &answer) {
		if (node == nullptr) {
			return false;
		}
		if (kthSmallest(node->left, k, count, answer)) {
			return true;
		}
		++count;
		if (count == k) {
			answer = node->value;
			return true;
		}
		return kthSmallest(node->right, k, count, answer);
	}

	inline void serialize(BinaryNode *node, std::ostream &out) {
		if (node == nullptr) {
			out << '#';
			return;
		}
		out << node->value << ',';
		serialize(node->left, out);
		out << ',';
		serialize(node->right, out);
	}

	inline std::vector<std::string> splitCSV(const std::string &text) {
		std::vector<std::string> tokens;
		std::string current;
		for (char ch : text) {
			if (ch == ',') {
				if (!current.empty()) {
					tokens.push_back(current);
					current.clear();
				}
			} else if (!std::isspace(static_cast<unsigned char>(ch))) {
				current.push_back(ch);
			}
		}
		if (!current.empty()) {
			tokens.push_back(current);
		}
		return tokens;
	}

	inline BinaryNode *deserialize(const std::vector<std::string> &tokens, size_t &index) {
		if (index >= tokens.size()) {
			return nullptr;
		}
		if (tokens[index] == "#") {
			++index;
			return nullptr;
		}
		BinaryNode *node = new BinaryNode(std::stoi(tokens[index++]));
		node->left = deserialize(tokens, index);
		node->right = deserialize(tokens, index);
		return node;
	}

	inline BinaryNode *deserialize(const std::string &text) {
		std::vector<std::string> tokens = splitCSV(text);
		size_t index = 0;
		return deserialize(tokens, index);
	}
}