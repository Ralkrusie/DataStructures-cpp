/*
【问题描述】

n皇后问题研究的是如何将n个皇后放置在n×n的棋盘上，并且使皇后彼此之间不能相互攻击。给定一个整数n，返回n皇后不同的解决方案的数量。要求设计如下函数：

class Solution{
public:
 int totalNQueens(int n)
 {  … }
};
【输入形式】

      输入一个整数n。

【输出形式】

        输出n皇后问题的解决方案的数量。

【样例输入】

6

【样例输出】

     4

【样例说明】

      6皇后问题有4个不同的求解方案。测试数据存放在in.txt文件中。

*/

#include <fstream>
#include <iostream>
#include <vector>

class Solution {
public:
    int totalNQueens(int n) {
        // column 记录每一列是否已经放过皇后，
        // 主对角线上的位置的特征：row + col 是常数；
        // 副对角线上的位置的特征：row - col 是常数，row - col + n - 1 可以将范围调整为非负数。
        // diag1 记录“主对角线”(row + col) 是否被占用，
        // diag2 记录“副对角线”(row - col + n - 1) 是否被占用。
        // 这样可以在 O(1) 时间判断当前位置能不能放皇后。
        std::vector<bool> column(n, false);
        std::vector<bool> diag1(2*n-1, false);
        std::vector<bool> diag2(2*n-1, false);
        return backtrack(0, n, column, diag1, diag2);
    }

private:
    int backtrack(int row, int n, std::vector<bool> &column,
                  std::vector<bool> &diag1, std::vector<bool> &diag2) {
        // 递归到第 n 行，说明前 n 行都成功放置了皇后，找到一种合法方案。
        if (row == n) {
            return 1;
        }
        int count = 0;
        // 尝试在当前行的每一列放置皇后。
        for (int col = 0; col < n; ++col) {
            // 如果列或两个对角线已经被占用，则当前位置非法。
            if (column[col] || diag1[row + col] || diag2[row - col + n - 1]) {
                continue;
            }
            // 选择当前位置：标记列和对角线被占用。
            column[col] = diag1[row + col] = diag2[row - col + n - 1] = true;
            // 递归处理下一行。
            count += backtrack(row + 1, n, column, diag1, diag2);
            // 回溯：撤销当前选择，继续尝试本行其他列。
            column[col] = diag1[row + col] = diag2[row - col + n - 1] = false;
        }
        return count;
    }
};

int main() {
    int n;
    // 题目说明输入保存在 in.txt 中，这里直接按文件读取。
    std::ifstream fin("in.txt");
    fin >> n;

    Solution solution;
    int result = solution.totalNQueens(n);
    // 输出不同解法的总数。
    std::cout << result << '\n';
    return 0;
}