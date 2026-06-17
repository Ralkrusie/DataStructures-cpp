/*
3. 第九章第17题
【问题描述】给定一个使用除留余数法和拉链法解决冲突的哈希表 HashTable2 类（见课本9.4.3节），要求在该类中添加一个 remove(k) 算法，用于删除哈希表中关键字为 k 的元素。如果哈希表中存在关键字为 k 的元素，则将其删除；如果不存在，则不进行任何操作。

【输入形式】

第一行输入一个整数 n，表示接下来要进行的操作次数。


接下来 n行，每行输入一种操作，操作有两种类型：



“insert key value”，表示向哈希表中插入关键字为 key，值为 value 的元素，key 是整数，value 也是整数。

“remove key”，表示删除哈希表中关键字为 key 的元素。


【输出形式】

对于每一次 “remove key” 操作，如果成功删除关键字为 key 的元素，输出 “Delete successfully”；如果哈希表中不存在关键字为 key 的元素，输出 “Key not found”。

【样例输入】

5
insert 5 10
insert 15 20
remove 5
remove 10
insert 25 30
remove 25



【样例输出】

Delete successfully
Key not found
Delete successfully



【样例说明】

首先插入关键字为 5 值为 10 的元素和关键字为 15 值为 20 的元素到哈希表中。然后尝试删除关键字为 5 的元素，因为哈希表中存在该关键字，所以输出 “Delete successfully”；接着尝试删除关键字为 10 的元素，哈希表中不存在该关键字，输出 “Key not found”；插入关键字为 25 值为 30 的元素后，再删除关键字为 25 的元素，由于存在该关键字，输出 “Delete successfully”。【评分标准】
*/
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <utility>
#include <string>
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

    bool remove(int key) {
        int idx = hash(key);
        for (auto it = table[idx].begin(); it != table[idx].end(); ++it) {
            if (it->first == key) {
                table[idx].erase(it);
                return true;
            }
        }
        return false;
    }
};

int main() {
    int n;
    cin >> n;
    HashTable2 ht;
    string op;
    for (int i = 0; i < n; ++i) {
        cin >> op;
        if (op == "insert") {
            int key, value;
            cin >> key >> value;
            ht.insert(key, value);
        } else if (op == "remove") {
            int key;
            cin >> key;
            if (ht.remove(key)) {
                cout << "Delete successfully" << endl;
            } else {
                cout << "Key not found" << endl;
            }
        }
    }
    return 0;
}