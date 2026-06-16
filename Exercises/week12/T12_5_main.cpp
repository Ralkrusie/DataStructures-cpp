/*
【问题描述】


股票经纪人会对消息反应过度，由若干股票经纪人组成的一个股票经纪人社区，从一个股票经纪人传递消息另一个股票经纪人需要一定的时间，注意从A传递到B所花费的时间不一定与从B传递给A所花费的时间相同。你的任务是编写一个程序，该程序选择哪个股票经纪人作为消息的起点，以及该消息传播到整个股票经纪人社区所需的时间，该持续时间以最后一个人接收消息所需的时间来衡量。



【输入形式】


输入包含多组股票经纪人的数据，每组的第一行是股票经纪人数量n（1到100），每个人的编号从1到n。接下来每个股票经纪人对应一行，其格式是，他的联系人数量（m），后跟m对整数，分别为联系人编号和将消息传递给该联系人所花费的时间（以分钟为单位）。没有特殊的标点符号或间距规则。



【输出形式】


对于每组数据，输出一行包含消息传输最快的人的编号，以及在将该消息发送给此人之后，最后一个人多久后收到该消息，以整数分钟为单位。如果不能传递到某些人则输出"disjoint"。



【样例输入】

        5

        3 4 4 2 8 5 3

        1 5 8

        4 1 6 4 10 2 7 5 2

        0



        2 2 5 1 5






【样例输出】

        3 10



【样例说明】

       3号股票经纪人作为消息的起点，消息传播的最快，最后一个人10分钟后收到消息。测试数据存放在in.txt文件中。


【评分标准】

        共10个测试用例，每通过一个测试得10分。


*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

const int INF = 1e9;

int main() {
    ifstream fin("in.txt");
    int n;
    while (fin >> n) {
        if (n == 0) break;

        // 初始化距离矩阵
        vector<vector<int>> dist(n, vector<int>(n, INF));
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
        }

        // 读入每个股票经纪人的联系人信息
        for (int i = 0; i < n; ++i) {
            int m;
            fin >> m;
            for (int j = 0; j < m; ++j) {
                int v, t;
                fin >> v >> t;
                dist[i][v - 1] = t;  // 1-based → 0-based
            }
        }

        // Floyd-Warshall 求全源最短路径
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                if (dist[i][k] == INF) continue;
                for (int j = 0; j < n; ++j) {
                    if (dist[k][j] == INF) continue;
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        // 寻找最佳起点
        int best_broker = -1;
        int best_time = INF;

        for (int i = 0; i < n; ++i) {
            int max_time = 0;
            bool all_reachable = true;
            for (int j = 0; j < n; ++j) {
                if (dist[i][j] == INF) {
                    all_reachable = false;
                    break;
                }
                if (dist[i][j] > max_time) {
                    max_time = dist[i][j];
                }
            }
            if (all_reachable && max_time < best_time) {
                best_time = max_time;
                best_broker = i + 1;  // 转回 1-based
            }
        }

        if (best_broker == -1) {
            cout << "disjoint" << endl;
        } else {
            cout << best_broker << " " << best_time << endl;
        }
    }
    return 0;
}