/*
【问题描述】

某省调查城镇交通状况，得到现有城镇道路统计表，表中列出了每条道路直接连通的城镇。省政府“畅通工程”的目标是使全省任何两个城镇间都可以实现交通（但不一定有直接的道路相连，只要互相间接通过道路可达即可）。问最少还需要建设多少条道路？

【输入形式】

  每个测试用例的第1行给出两个正整数，分别是城镇数目n（n<1000）和道路数目m，随后的m行对应m条道路，每行给出一对正整数，分别是该条道路直接连通的两个城镇的编号。为简单起见，城镇从1到n编号。注意两个城市之间可以有多条道路相通，也就是说：

3 3

1 2

1 2

2 1

这种输入也是合法的。


【输出形式】对每个测试用例，在一行里输出最少还需要建设的道路数目。

【样例输入】

3 3

1 2

1 3

2 3

【样例输出】

0

【样例说明】
     测试数据的文件名为in.txt
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

void dfs(const std::vector<std::vector<int>>& graph, std::vector<bool>& visited, int start) {
  visited[start] = true;
  for (int neighbor : graph[start]) {
    if (!visited[neighbor]) {
      dfs(graph, visited, neighbor);
    }
  }
}


int main() {
  int n, m;
  std::ifstream fin("in.txt");
  fin >> n >> m;
  std::vector<std::vector<int>> graph(n + 1);
  for (int i = 0; i < m; ++i) {
    int a, b;
    fin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  std::vector<bool> visited(n + 1, false);
  int components = 0;
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      ++components;
      dfs(graph, visited, i);
    }
  }
  std::cout << components - 1 << std::endl;
  return 0;
}
