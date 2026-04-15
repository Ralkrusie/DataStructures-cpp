/*
2. 马踏棋盘
【问题描述】

      设计一个国际象棋的马踏遍棋盘的演示程序，是指将马随机放在国际象棋的8*8棋盘的 某个方格中，马按走棋规则（马走日字）进行移动。要求每个方格只进入一次，走遍棋盘上全部64个方格。探索方向固定顺序为：右下、右上、左上、左下、下右、下左、上左、上右。

【输入形式】

    给出马的起始位置，包括行下标和列下标
【输出形式】

    从马的起始位置开始，采用深度优先搜索的方式按顺序给出马遍历棋盘的下标，每一步用[ ]给出
【样例输入】

  0 0 

【样例输出】

[0,0][2,1][4,0][6,1][7,3][6,5][7,7][5,6][6,4][7,2][5,3][7,4][6,6][4,7][5,5][6,3][7,1][5,2][6,0][4,1][6,2][7,0][5,1][4,3][3,5][5,4][7,5][6,7][4,6][2,7][0,6][1,4][2,2][3,0][4,2][5,0][3,1][2,3][4,4][3,6][5,7][7,6][4,5][3,7][1,6][2,4][3,2][1,3][3,4][2,6][0,7][1,5][0,3][1,1][0,5][1,7][2,5][3,3][1,2][2,0][0,1][0,4][0,2][1,0]

【样例说明】
【评分标准】

    一共有5个测试用例，允许使用STL。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

static const int N = 8;
static const int dr[8] = {1, 2, 2, 1, -1, -2, -2, -1};
static const int dc[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

bool isInsideBoard(int rowIndex, int colIndex) {
    return rowIndex >= 0 && rowIndex < N && colIndex >= 0 && colIndex < N;
}

bool depthFirstSearch(
    int currentRow,
    int currentCol,
    int visitedCellCount,
    bool visited[N][N],
    vector<pair<int, int>>& traversalPath) {

    if (visitedCellCount == N * N) {
        return true;
    }

    for (int moveIndex = 0; moveIndex < 8; ++moveIndex) {
        int nextRow = currentRow + dr[moveIndex];
        int nextCol = currentCol + dc[moveIndex];
        if (isInsideBoard(nextRow, nextCol) && !visited[nextRow][nextCol]) {
        visited[nextRow][nextCol] = true;
        traversalPath.push_back({nextRow, nextCol});

        if (depthFirstSearch(nextRow, nextCol, visitedCellCount + 1, visited, traversalPath)) {
            return true;
        }

        traversalPath.pop_back();
        visited[nextRow][nextCol] = false;
        }
    }
    return false;
}

int main() {
    int startRow, startCol;
    if (!(cin >> startRow >> startCol)) {
        return 0;
    }

    bool visited[N][N] = {false};
    vector<pair<int, int>> traversalPath;
    traversalPath.reserve(N * N);

    visited[startRow][startCol] = true;
    traversalPath.push_back({startRow, startCol});

    bool hasSolution = depthFirstSearch(startRow, startCol, 1, visited, traversalPath);

    if (hasSolution) {
        for (const auto& position : traversalPath) {
            cout << '[' << position.first << ',' << position.second << ']';
        }
        cout << '\n';
    } else {
        cout << "No solution\n";
    }

    return 0;
}
