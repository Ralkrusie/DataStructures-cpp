#include <iostream>
#include <stack>
#include <vector>
using namespace std;

const int N = 8
;

int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

int main(){
    cout << "正在测试所有起点..." << endl;
    vector<pair<int,int>> failed;

    for(int sx = 0; sx < N; ++sx){
        for(int sy = 0; sy < N; ++sy){
            bool visited[N][N] = {false};

            stack<pair<int, int>> s;
            s.push({sx, sy});

            int step = 0;
            while(!s.empty()){
                pair<int, int> currp = s.top();
                s.pop();

                int cx = currp.first;
                int cy = currp.second;

                if(visited[cx][cy]) continue;

                visited[cx][cy] = true;
                step++;

                if(step == N * N) break;

                for(int i = 7; i >= 0; --i){
                    int nx = cx + dx[i];
                    int ny = cy + dy[i];

                    if(nx >= 0 && nx < N && ny >= 0 && ny < N && !visited[nx][ny]){
                        s.push({nx, ny});
                    }
                }
            }

            if (step < N * N) {
                failed.push_back({sx, sy});
            }
        }
    }

    if(failed.empty()){
        cout << "所有起点均能找到完整路径。" << endl;
    } else {
        cout << "无法找到完整路径的起点：";
        for(auto &p : failed){
            cout << "[" << p.first << "," << p.second << "] ";
        }
        cout << endl;
    }

    return 0;
}
