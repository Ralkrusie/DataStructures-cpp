/*
13. 并查集-路径压缩与按秩合并
并查集-路径压缩与按秩合并
一、问题描述
实现一个并查集（Union-Find），支持以下操作：

union x y：合并包含x和y的集合

query x：查找x所在集合的代表元素（根节点）以及集合大小

same x y：判断x和y是否在同一个集合

要求实现路径压缩和按秩合并优化。

二、输入形式
第一行输入两个正整数n和m（1 ≤ n ≤ 100000, 1 ≤ m ≤ 100000），分别表示元素数量和操作数量。
接下来m行，每行一个操作，格式如上所述。元素编号为0到n-1。

三、输出形式
对于 query 操作，输出代表元素和集合大小，空格分隔。

对于 same 操作，输出 "Yes" 或 "No"。
每个输出占一行。

四、样例输入

5 6
union 0 1
union 2 3
query 0
same 0 2
union 1 2
same 0 3
五、样例输出
0 2
No
Yes
六、样例说明
操作过程：

union 0 1：集合{0,1}, {2}, {3}, {4}

union 2 3：集合{0,1}, {2,3}, {4}

query 0：代表元素为0（或1），集合大小为2，输出 0 2

same 0 2：不在同一集合，输出 No

union 1 2：合并{0,1}和{2,3}，得到{0,1,2,3}

same 0 3：在同一集合，输出 Yes

七、评分标准
共10个测试用例。

八、类库使用要求
只能使用数组实现并查集，禁止使用其他数据结构。
*/

#include <iostream>
#include <string>

class DisjointSet {
public:
	explicit DisjointSet(int n) : parent(new int[n]), rank(new int[n]), setSize(new int[n]) {
		for (int i = 0; i < n; ++i) {
			parent[i] = i;
			rank[i] = 0;
			setSize[i] = 1;
		}
	}

	~DisjointSet() {
		delete[] parent;
		delete[] rank;
		delete[] setSize;
	}

	int find(int x) {
		if (parent[x] != x) {
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}

	void unite(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) {
			return;
		}
		if (rank[a] < rank[b]) {
			int tmp = a;
			a = b;
			b = tmp;
		}
		parent[b] = a;
		setSize[a] += setSize[b];
		if (rank[a] == rank[b]) {
			++rank[a];
		}
	}

	int componentSize(int x) {
		return setSize[find(x)];
	}

private:
	int *parent;
	int *rank;
	int *setSize;
};

int main() {
	int n, m;
	std::cin >> n >> m;
	DisjointSet ds(n);
	std::string op;
	for (int i = 0; i < m; ++i) {
		std::cin >> op;
		if (op == "union") {
			int x, y;
			std::cin >> x >> y;
			ds.unite(x, y);
		} else if (op == "query") {
			int x;
			std::cin >> x;
			std::cout << ds.find(x) << ' ' << ds.componentSize(x) << '\n';
		} else if (op == "same") {
			int x, y;
			std::cin >> x >> y;
			std::cout << (ds.find(x) == ds.find(y) ? "Yes" : "No") << '\n';
		}
	}
	return 0;
}