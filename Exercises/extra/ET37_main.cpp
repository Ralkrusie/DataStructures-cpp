/*
12. 二叉树重建-根据遍历序列
二叉树重建-根据遍历序列
一、问题描述
给定一棵二叉树的先序遍历和中序遍历序列，重建这棵二叉树，并输出后序遍历序列。

二、输入形式
第一行一个数，表示节点个数。
第二行输入若干个整数，表示先序遍历序列。
第三行输入若干个整数，表示中序遍历序列。
两个序列长度相同，节点值互不相同。

三、输出形式
输出后序遍历序列，用空格分隔。

四、样例输入

5 
3 9 20 15 7
9 3 15 20 7
五、样例输出

9 15 7 20 3
六、样例说明
先序：3 9 20 15 7
中序：9 3 15 20 7

重建过程：

先序第一个元素3是根节点

在中序中找到3，左边[9]是左子树，右边[15,20,7]是右子树

递归重建左子树：先序[9]，中序[9]

递归重建右子树：先序[20,15,7]，中序[15,20,7]

后序遍历：9 15 7 20 3

七、评分标准
共10个测试用例。

八、类库使用要求
必须手动实现二叉树结构。
*/

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../Structures/et_tree_utils.hpp"

static std::vector<int> parseLineInts(const std::string &line) {
	std::vector<int> values;
	std::stringstream ss(line);
	int x;
	while (ss >> x) {
		values.push_back(x);
	}
	return values;
}

static et::BinaryNode *buildFromPreIn(const std::vector<int> &preorder, int preLeft, int preRight,
	const std::vector<int> &inorder, int inLeft, int inRight, const std::unordered_map<int, int> &positions) {
	if (preLeft >= preRight) {
		return nullptr;
	}
	int rootValue = preorder[preLeft];
	int rootIndex = positions.at(rootValue);
	int leftSize = rootIndex - inLeft;
	et::BinaryNode *root = new et::BinaryNode(rootValue);
	root->left = buildFromPreIn(preorder, preLeft + 1, preLeft + 1 + leftSize, inorder, inLeft, rootIndex, positions);
	root->right = buildFromPreIn(preorder, preLeft + 1 + leftSize, preRight, inorder, rootIndex + 1, inRight, positions);
	return root;
}

int main() {
	int n;
	std::cin >> n;
	std::string line;
	std::getline(std::cin, line);
	while (line.empty() && std::getline(std::cin, line)) {
	}
	std::vector<int> preorder = parseLineInts(line);
	line.clear();
	while (line.empty() && std::getline(std::cin, line)) {
	}
	std::vector<int> inorder = parseLineInts(line);

	std::unordered_map<int, int> positions;
	for (int i = 0; i < static_cast<int>(inorder.size()); ++i) {
		positions[inorder[i]] = i;
	}

	et::BinaryNode *root = buildFromPreIn(preorder, 0, static_cast<int>(preorder.size()), inorder, 0,
		static_cast<int>(inorder.size()), positions);
	bool first = true;
	et::postorder(root, first);
	std::cout << '\n';
	et::destroy(root);
	return 0;
}