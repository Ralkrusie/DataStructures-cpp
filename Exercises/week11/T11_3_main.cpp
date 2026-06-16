/*
【问题描述】

   对于一组符号，每个符号有一个编码，如果没有一个符号编码是另一个符号编码的前缀，则称该组符号编码是可立即解码。假设所有编码是二进制的，一组编码中没有两个编码是相同的，每个编码至少有一位且不超过500位，并且每组符号编码至少有两个，但不超过500个。

【输入形式】

    有多行字符串，每一行是一串二进制字符串表示一个符号编码，最后一行是9，表示字符串结束。

【输出形式】

          是可立即解码的编码，输出“Y”，不是可立即解码的编码，输出‘N’。
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
   vector<string> codes;
   string line;
   ifstream fin("in.txt");
   while (getline(fin, line)) {
      if (line == "9") break;
      codes.push_back(line);
   }

   sort(codes.begin(), codes.end());
   bool ok = true;
   for (size_t i = 0; i + 1 < codes.size(); ++i) {
      const string &a = codes[i];
      const string &b = codes[i+1];
      if (b.size() >= a.size() && b.compare(0, a.size(), a) == 0) {
         ok = false;
         break;
      }
   }

   cout << (ok ? 'Y' : 'N') << '\n';
   return 0;
}
