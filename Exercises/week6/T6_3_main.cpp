/*
3. 串的模式匹配
问题描述】子串出现次数问题：基于KMP算法实现输出字符串t在主串S中出现的次数。
【输入形式】

第一行，输入子串字符串t

第二行，输入主串字符串S

【样例输入】

abcab

aabcabcabaabcab

【样例输出】

3
【样例说明】标准输入输出

【评分标准】10个测试用例，每通过一个计10分，没有用KMP算法计0分。  

允许使用STL类库
*/


#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> getNext(const string& pattern) {
    vector<int> next(pattern.size(), 0);
    size_t j = 0;
    for (size_t i = 1; i < pattern.size(); ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        next[i] = static_cast<int>(j);
    }
    return next;
}

int kmp_count(string str, string pattern) {
    if (pattern.empty() || str.empty()) {
        return 0;
    }

    vector<int> next = getNext(pattern);
    size_t pCur = 0;
    int count = 0;

    for (size_t sCur = 0; sCur < str.size(); ++sCur) {
        while (pCur > 0 && str[sCur] != pattern[pCur]) {
            pCur = static_cast<size_t>(next[pCur - 1]);
        }
        if (str[sCur] == pattern[pCur]) {
            ++pCur;
        }

        if (pCur == pattern.size()) {
            ++count;
            pCur = static_cast<size_t>(next[pCur - 1]);
        }
    }
    return count;
}

int main() {
    string pattern, str;
    cin >> pattern >> str;
    int count = kmp_count(str, pattern);
    cout << count << endl;
    return 0;
}