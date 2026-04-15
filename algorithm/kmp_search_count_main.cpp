#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> getNext(const string& pattern);

int kmp_search_count(string str, string pattern) {
	if (pattern.empty()) {
		return 0;
	}

	vector<int> next = getNext(pattern);
	int pCur = 0;
	int strLen = static_cast<int>(str.size());
	int patternLen = static_cast<int>(pattern.size());
	int count = 0;

	for (int sCur = 0; sCur < strLen; sCur++) {
		while (pCur > 0 && str[sCur] != pattern[pCur]) {
			pCur = next[pCur - 1];
		}
		if (str[sCur] == pattern[pCur]) {
			pCur++;
		}

		if (pCur == patternLen) {
			count++;
			pCur = next[pCur - 1];
		}
	}
	return count;
}

vector<int> getNext(const string& pattern) {
	vector<int> next(pattern.size(), 0);
	int pCur = 0;
	for (int cur = 1; cur < pattern.size(); cur++) {
		while (pCur > 0 && pattern[cur] != pattern[pCur]) {
			pCur = next[pCur - 1];
		}
		if (pattern[cur] == pattern[pCur]) {
			pCur++;
		}
		next[cur] = pCur;
	}
	return next;
}

int main() {
	string s, t;
	cin >> s >> t;
	cout << kmp_search_count(s, t) << endl;
	return 0;
}
