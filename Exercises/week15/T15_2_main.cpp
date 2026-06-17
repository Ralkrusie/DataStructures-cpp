/*
2. 第九章第18题
【问题描述】给定一个使用除留余数法和拉链法解决冲突的哈希表 HashTable2 类（见9.4.3节），要求在该类中添加一个 ASL1() 算法，用于计算在成功查找情况下的平均查找长度（Average Search Length，ASL）。成功查找情况下的平均查找长度是指为确定记录在哈希表中的位置，在查找成功时对关键字进行比较的平均次数。

【输入形式】

第一行输入一个整数 n，表示接下来要进行插入操作的次数。
接下来 n 行，每行输入两个整数 key 和 value，表示向哈希表中插入关键字为 key，值为 value 的元素。

【输出形式】

输出一个整数，表示成功情况下的平均查找长度，结果向下取整。

【样例输入】

5
3 30
7 70
13 130
17 170
23 230

【样例输出】

1


【样例说明】
通过除留余数法（假设哈希表长度合适）和拉链法将 5 个元素插入哈希表中，每个元素在各自的链表中查找时只需要比较 1 次（因为没有冲突，各自在单独的链表中），所以成功情况下的平均查找长度为 (1 + 1 + 1 + 1 + 1) / 5 = 1。
*/
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <utility>
using namespace std;

class HashTable2 {
private:
    static const int TABLE_SIZE = 10007;
    vector<list<pair<int, int>>> table;

    int hash(int key) const {
        return key % TABLE_SIZE;
    }

public:
    HashTable2() : table(TABLE_SIZE) {}

    void insert(int key, int value) {
        int idx = hash(key);
        for (auto& p : table[idx]) {
            if (p.first == key) {
                p.second = value;
                return;
            }
        }
        table[idx].push_back({key, value});
    }

    int ASL1() const {
        int totalComparisons = 0;
        int totalElements = 0;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            int chainLen = (int)table[i].size();
            if (chainLen > 0) {
                totalComparisons += chainLen * (chainLen + 1) / 2;
                totalElements += chainLen;
            }
        }
        if (totalElements == 0) return 0;
        return totalComparisons / totalElements;
    }
};

int main() {
    int n;
    cin >> n;
    HashTable2 ht;
    for (int i = 0; i < n; ++i) {
        int key, value;
        cin >> key >> value;
        ht.insert(key, value);
    }
    cout << ht.ASL1() << endl;
    return 0;
}