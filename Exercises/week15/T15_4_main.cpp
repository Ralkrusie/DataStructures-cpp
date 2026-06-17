/*
4. 实战9.3POJ2418-硬木的种类
【问题描述】

     硬木是植物树群，有宽阔的叶子，产生水果或坚果，并且通常在冬天休眠。美国的温带气候产生了数百种硬木树种。例如橡树、枫树和樱桃都是硬木树种，它们是不同的物种。硬木树种的数目共占美国数木的40%。利用卫星成像技术，自然资源部编制了一份特定日期的每棵树的清单。这里需要计算每个树种的总分数。
【输入形式】

     每行表示一棵树的树种，树种的名字不超过30个字符。所有树种不超过10000种，不超过1000000棵树。
【输出形式】

     按字母顺序输出每个树种的名称以及对应的百分比，百分比精确到第4个小数位。
【样例输入】

Red Alder

Red Alder

Ash

Ash

【样例输出】

Ash 50.0000

Red Alder 50.0000

【样例说明】

     测试数据的文件名为in.txt

【评分标准】

    该题目有5个测试用例，每通过一个测试用例，得20分。


*/
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    ifstream fin("in.txt");
    map<string, int> count;
    string species;
    int total = 0;
    while (getline(fin, species)) {
        if (species.empty()) continue;
        count[species]++;
        total++;
    }

    cout << fixed << setprecision(4);
    for (const auto& p : count) {
        double percent = 100.0 * p.second / total;
        cout << p.first << " " << percent << endl;
    }
    return 0;
}