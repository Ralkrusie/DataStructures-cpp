#include <iostream>
#include <vector>
#include <utility>

class UnionFind {
public:
	explicit UnionFind(int n) : parent(n), rank(n, 0), size(n, 1) {
		for (int i = 0; i < n; ++i) {
			parent[i] = i;
		}
	}

	int find(int x) {
		if (parent[x] == x) {
			return x;
		}
		return parent[x] = find(parent[x]); // 路径压缩
	}

	void unite(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) {
			return;
		}

		if (rank[a] < rank[b]) {
			std::swap(a, b);
		}

		parent[b] = a;
		size[a] += size[b];
		if (rank[a] == rank[b]) {
			++rank[a];
		}
	}

	bool same(int a, int b) {
		return find(a) == find(b);
	}

	int componentSize(int x) {
		return size[find(x)];
	}

private:
	std::vector<int> parent;    // parent[i] 是 i 的父节点，如果 parent[i] == i 则 i 是一个集合的代表元素（根节点）。
	std::vector<int> rank;  // 用于按秩合并，秩可以理解成树高的一个近似上界，不是精确高度。
	std::vector<int> size;  // size[i] 是以 i 为代表元素的集合的大小，仅在 i 是根节点时有效。
};

int main() {
	UnionFind uf(6);

	uf.unite(0, 1);
	uf.unite(2, 3);
	uf.unite(1, 2);

	std::cout << "0 和 3 是否在同一集合: " << (uf.same(0, 3) ? "Yes" : "No") << '\n';
	std::cout << "0 所在集合的代表元素: " << uf.find(0) << '\n';
	std::cout << "0 所在集合的大小: " << uf.componentSize(0) << '\n';
	std::cout << "4 所在集合的大小: " << uf.componentSize(4) << '\n';

	return 0;
}

