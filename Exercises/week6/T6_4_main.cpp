/*
4. 5.2.1LeetCode48—旋转图像
【问题描述】

   给定一个n×n的二维矩阵表示一个图像。将图像顺时针旋转90度。你必须在原地旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要使用另一个矩阵来旋转图像。例如，给定matrix={{1，2，3}，{4，5，6}，{7，8，9}}，原地旋转输入矩阵，使其变为{{7，4，1}，{8，5，2}，{9，6，3}}。

【输入形式】

    每个测试用例的第一行为n（1≤n≤800），接下来n行每行n个整数，表示矩阵a，第i行的第j个整数为aij（-10^8≤aij≤10^8）

  
【输出形式】对于每个测试用例，输出n行每行n个整数表示矩阵旋转之后的结果。

【样例输入】

4

5 1 9 11

2 4 8 10

13 3 6 7

15 14 12 16


【样例输出】

15 13 2 5

14 3 4 1

12 6 8 9

16 7 10 11

【样例说明】

     测试数据的文件名为in.txt
*/

#include <iostream>
#include <vector>
#include <fstream>

class Matrix {
public:
    Matrix(size_t n) : n(n), data(n, std::vector<int>(n)) {}

    void readFromStream(std::istream& in) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                in >> data[i][j];
            }
        }
    }

    void rotate() {
        for (size_t i = 0; i < n / 2; ++i) {
            for (size_t j = i; j < n - i - 1; ++j) {
                int temp = data[i][j];
                data[i][j] = data[n - j - 1][i];
                data[n - j - 1][i] = data[n - i - 1][n - j - 1];
                data[n - i - 1][n - j - 1] = data[j][n - i - 1];
                data[j][n - i - 1] = temp;
            }
        }
    }

    void print() const {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                std::cout << data[i][j] << (j == n - 1 ? '\n' : ' ');
            }
        }
    }



private:
    size_t n;
    std::vector<std::vector<int>> data;
};

int main() {
    size_t n;
    std::ifstream fin;
    std::istream* input = &std::cin;

    if (!(std::cin >> n)) {
        std::cin.clear();
        fin.open("in.txt");
        if (!(fin >> n)) {
            return 0;
        }
        input = &fin;
    }

    Matrix matrix(n);
    matrix.readFromStream(*input);
    matrix.rotate();
    matrix.print();
    return 0;
}