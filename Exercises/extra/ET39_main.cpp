/*
14. 表达式树求值
表达式树求值
一、问题描述
给定一个表达式树，求表达式的值。表达式树中叶子节点是整数，内部节点是运算符（+、-、*、/）。

输入格式：每行表示一个节点，格式为"id type value left right"，id为节点编号，type为0（数字）或1（运算符），value为数字值或运算符字符，left和right为左右子节点编号（-1表示无）。

二、输入形式
第一行输入一个正整数n，表示节点数量。
接下来n行，每行描述一个节点。

三、输出形式
输出一个整数，表示表达式的值。除法为整数除法，向零取整。

四、样例输入

5
0 0 3 -1 -1
1 0 4 -1 -1
2 1 + 0 1
3 0 2 -1 -1
4 1 * 2 3
五、样例输出

14
六、样例说明
表达式树结构：

      *
     / \
    +   2
   / \
  3   4
计算过程：(3 + 4) * 2 = 14

七、评分标准
共8个测试用例。

八、类库使用要求
可以使用数组存储节点。
*/

#include <iostream>
#include <string>
#include <vector>

struct ExprNode {
  int type;
  long long number;
  char op;
  int left;
  int right;
};

static long long evaluate(const std::vector<ExprNode> &nodes, int index) {
  const ExprNode &node = nodes[index];
  if (node.type == 0) {
    return node.number;
  }
  long long leftValue = evaluate(nodes, node.left);
  long long rightValue = evaluate(nodes, node.right);
  switch (node.op) {
  case '+':
    return leftValue + rightValue;
  case '-':
    return leftValue - rightValue;
  case '*':
    return leftValue * rightValue;
  default:
    return leftValue / rightValue;
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<ExprNode> nodes(n);
  std::vector<int> indegree(n, 0);
  for (int i = 0; i < n; ++i) {
    int id, type, left, right;
    std::string value;
    std::cin >> id >> type >> value >> left >> right;
    nodes[id].type = type;
    nodes[id].left = left;
    nodes[id].right = right;
    if (type == 0) {
      nodes[id].number = std::stoll(value);
    } else {
      nodes[id].op = value[0];
    }
    if (left != -1) {
      ++indegree[left];
    }
    if (right != -1) {
      ++indegree[right];
    }
  }
  int root = 0;
  for (int i = 0; i < n; ++i) {
    if (indegree[i] == 0) {
      root = i;
      break;
    }
  }
  std::cout << evaluate(nodes, root) << '\n';
  return 0;
}