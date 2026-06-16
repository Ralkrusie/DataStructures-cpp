#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void mergeRange(vector<int>& nums, vector<int>& temp, int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	int k = left;

	while (i <= mid && j <= right) {
		if (nums[i] <= nums[j]) {
			temp[k++] = nums[i++];
		} else {
			temp[k++] = nums[j++];
		}
	}

	while (i <= mid) {
		temp[k++] = nums[i++];
	}

	while (j <= right) {
		temp[k++] = nums[j++];
	}

	for (int idx = left; idx <= right; ++idx) {
		nums[idx] = temp[idx];
	}
}

void mergeSortRecursive(vector<int>& nums, vector<int>& temp, int left, int right) {
	if (left >= right) {
		return;
	}

	int mid = left + (right - left) / 2;
	mergeSortRecursive(nums, temp, left, mid);
	mergeSortRecursive(nums, temp, mid + 1, right);
	mergeRange(nums, temp, left, mid, right);
}

void mergeSortRecursive(vector<int>& nums) {
	if (nums.empty()) {
		return;
	}

	vector<int> temp(nums.size());
	mergeSortRecursive(nums, temp, 0, static_cast<int>(nums.size()) - 1);
}

void mergeSortIterative(vector<int>& nums) {
	int n = static_cast<int>(nums.size());
	if (n <= 1) {
		return;
	}

	vector<int> temp(n);
	for (int step = 1; step < n; step *= 2) {
		for (int left = 0; left < n; left += step * 2) {
			int mid = min(left + step - 1, n - 1);
			int right = min(left + step * 2 - 1, n - 1);

			if (mid >= right) {
				continue;
			}

			mergeRange(nums, temp, left, mid, right);
		}
	}
}

void printVector(const vector<int>& nums) {
	for (size_t i = 0; i < nums.size(); ++i) {
		if (i > 0) {
			cout << ' ';
		}
		cout << nums[i];
	}
	cout << '\n';
}

int main() {
	int n;
	vector<int> nums;

	if (cin >> n) {
		nums.resize(n);
		for (int i = 0; i < n; ++i) {
			cin >> nums[i];
		}
	} else {
		nums = {8, 3, 5, 1, 9, 6, 2, 7, 4};
	}

	vector<int> recursiveNums = nums;
	vector<int> iterativeNums = nums;

	mergeSortRecursive(recursiveNums);
	mergeSortIterative(iterativeNums);

	cout << "递归归并排序结果:" << '\n';
	printVector(recursiveNums);
	cout << "非递归归并排序结果:" << '\n';
	printVector(iterativeNums);

	return 0;
}
