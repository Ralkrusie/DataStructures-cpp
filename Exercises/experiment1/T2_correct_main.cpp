#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
bool visited[8][8] = {false};

int main(){
    int x, y;
    cin >> x >> y;

    stack<pair<int, int>> s;
    s.push({x, y});

    int step = 0;
    while(!s.empty()){
        pair<int, int> currp = s.top();
        s.pop();

        int cx = currp.first;
        int cy = currp.second;

        if(visited[cx][cy]) continue;

        visited[cx][cy] = true;
        cout << "[" << cx << "," << cy << "]";
        step++;

        if(step == 64) break;

        for(int i = 7; i >= 0; --i){
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if(nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && !visited[nx][ny]){
                s.push({nx, ny});
            }
        }
    }

    if (step < 64){
        cout << "贪心算法无法从这一起始点开始找到完整的路径！";
    }

    return 0;
}
