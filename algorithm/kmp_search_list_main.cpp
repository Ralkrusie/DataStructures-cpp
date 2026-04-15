#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> getNext(const string& pattern);

vector<int> kmp_search_list(string str, string pattern) {
	vector<int> positions;
	if (pattern.empty()) {
		return positions;
	}

	vector<int> next = getNext(pattern);
	int pCur = 0;
	int strLen = static_cast<int>(str.size());
	int patternLen = static_cast<int>(pattern.size());

	for (int sCur = 0; sCur < strLen; sCur++) {
		while (pCur > 0 && str[sCur] != pattern[pCur]) {
			pCur = next[pCur - 1];
		}
		if (str[sCur] == pattern[pCur]) {
			pCur++;
		}

		if (pCur == patternLen) {
			positions.push_back(sCur - patternLen + 1);
			pCur = next[pCur - 1];
		}
	}
	return positions;
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

	vector<int> positions = kmp_search_list(s, t);
	if (positions.empty()) {
		cout << -1 << endl;
		return 0;
	}

	for (int i = 0; i < positions.size(); i++) {
		if (i > 0) {
			cout << ' ';
		}
		cout << positions[i];
	}
	cout << endl;
	return 0;
}
