/*
【问题描述】

一个无向图采用邻接表存储，设计一个算法在存在经过顶点v的简单回路时输出所有这样的简单回路

【输入形式】

n m（点数、边数）

u1 v1(一条边连接u1和v1)

…

um vm

v(询问的顶点)

【输出形式】

将经过v的简单回路上的点按编号从小到大排序，并顺序输出，如

v1 v2 … vk (k为环长)

若有多条经过v的简单回路，将点编号排序后的回路按字典序从小到大排序，并输出，不同回路之间换行分隔

若没有经过v的简单回路，输出-1

【样例输入】

4 5

1 2

2 3

3 1

3 4

1 4

1

【样例输出】

1 2 3 

1 2 3 4

1 3 4

【评分标准】

n<=200，无重边自环
*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <cstddef>
using namespace std;

int n, m;
vector<vector<int>> g;
int startV;
vector<char> visited;
set<vector<int>> cycles; // 存放已排序且去重的回路顶点列表

void dfs(int u, int parent, vector<int>& path){
	for(int v: g[u]){
		if(v == startV){
			if(path.size() >= 3){
				set<int> s(path.begin(), path.end());
				vector<int> vec(s.begin(), s.end());
				cycles.insert(vec);
			}
			continue;
		}
		if(v == parent) continue;
		if(!visited[v]){
			visited[v] = 1;
			path.push_back(v);
			dfs(v, u, path);
			path.pop_back();
			visited[v] = 0;
		}
	}
}

int main(){
	if(!(cin >> n >> m)) return 0;
	g.assign(n+1, {});
	for(int i = 0; i < m; ++i){
		int u, v; cin >> u >> v;
		if(u >=1 && u <= n && v >=1 && v <= n){
			g[u].push_back(v);
			g[v].push_back(u);
		}
	}
	cin >> startV;

	for(int i = 1; i <= n; ++i) sort(g[i].begin(), g[i].end());

	visited.assign(n+1, 0);
	visited[startV] = 1;
	vector<int> path;
	path.push_back(startV);

	// 从 startV 的每个邻居开始 DFS，记录遇到回到 startV 的路径
	for(int v: g[startV]){
		if(!visited[v]){
			visited[v] = 1;
			path.push_back(v);
			dfs(v, startV, path);
			path.pop_back();
			visited[v] = 0;
		}
	}

	if(cycles.empty()){
		cout << -1;
		return 0;
	}

	// cycles 中的每个 vector 都是升序的点集合，set 保证了按字典序输出
	for(const auto &vec: cycles){
		for(size_t i = 0; i < vec.size(); ++i){
			if(i) cout << ' ';
			cout << vec[i];
		}
		cout << '\n';
	}

	return 0;
}