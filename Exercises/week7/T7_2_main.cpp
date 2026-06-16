/*
2. LeetCode46—全排列
【问题描述】


给定一个没有重复数字的序列，返回其所有可能的全排列。例如，输入[1，2，3]，输出为[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]。



【输入形式】



      输入一个没有重复数字的整数序列。


【输出形式】

      输出该数字序列的全排列序列。


【样例输入】

      1 2 3


【样例输出】

     1 2 3

     1 3 2

     2 1 3

     2 3 1

     3 1 2

     3 2 1


【样例说明】

     输入没有重复的三个整数，输出3!
=6个整数序列，每行显示一个排列。测试数据存放在in.txt文件中。
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void backtrack(std::vector<int> &nums, std::vector<bool> &used,
               std::vector<int> &current,
               std::vector<std::vector<int>> &result) {
    if (current.size() == nums.size()) {
        result.push_back(current);
        return;
    }
    for (size_t i = 0; i < nums.size(); ++i) {
        if (used[i]) {
            continue;
        }
        used[i] = true;
        current.push_back(nums[i]);
        backtrack(nums, used, current, result);
        current.pop_back();
        used[i] = false;
    }
}

std::vector<std::vector<int>> permute(std::vector<int> &nums) {
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    std::vector<bool> used(nums.size(), false);
    backtrack(nums, used, current, result);
    return result;
}

int main() {
    std::vector<int> nums;
    std::ifstream fin("in.txt");
    int num;
    while (fin >> num) {
        nums.push_back(num);
    }

    std::vector<std::vector<int>> permutations = permute(nums);
    for (const auto &perm : permutations) {
        bool first = true;
        for (const int &num : perm) {
            if (!first) {
                std::cout << ' ';
            }
            std::cout << num;
            first = false;
        }
        std::cout << '\n';
    }
    return 0;
}