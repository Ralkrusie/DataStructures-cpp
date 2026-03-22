#include <iostream>
#include <vector>
#include <algorithm>

int minDiff(const std::vector<int> &vec,const int &pos) {
    int min = std::abs(vec[pos] - vec[0]);
    for (int i = 0; i < pos; ++i) {
        int current = std::abs(vec[pos] - vec[i]);
        if (current < min) {
            min = current;
        }
    }
    return min;
}


int main() {
    int n;
    std::cin >> n;
    std::vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> values[i];
    }
    int sum = values[0];
    for (int i = 1; i < n; ++i) {
        sum += minDiff(values, i);
    }
    std::cout << sum << std::endl;

    return 0;
}