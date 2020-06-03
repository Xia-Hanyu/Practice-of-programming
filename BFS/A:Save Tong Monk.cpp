/*
 * @Author: Xia Hanyu
 * @Date:   2020-06-03 13:09:23
 * @Last Modified by:   Xia Hanyu
 * @Last Modified time: 2020-06-03 16:06:01
 */
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <limits>

using namespace std;

struct node {
    int x, y, key, step, snake_state;
    node(int x_, int y_, int key_, int step_, int state)
        : x(x_), y(y_), key(key_), step(step_), snake_state(state) {}
};

map<pair<int, int>, int> snake;
int n, m;
char maze[105][105];
int visited[105][105][10][50];
int dx[] = {0, -1, 0, 1}, dy[] = {1, 0, -1, 0};

int main(int argc, char const *argv[]) {
    while (cin >> n >> m && n != 0) {
        vector<int> ans;
        memset(visited, 0, sizeof(visited));
        snake.clear();
        int snake_cnt = 0;
        int startx, starty, snake_state = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                cin >> maze[i][j];
                if (maze[i][j] == 'S') {
                    snake[make_pair(i, j)] = snake_cnt;
                    snake_state |= (1 << snake_cnt);
                    snake_cnt++;
                }
                if (maze[i][j] == 'K') {
                    startx = i, starty = j;
                }
            }
        queue<node> path;
        path.push(node(startx, starty, 0, 0, snake_state));
        bool finish = false;
        while (!path.empty()) {
            for (int i = 0; i < 4; ++i) {
                int tempx = path.front().x + dx[i],
                    tempy = path.front().y + dy[i];
                // 出界/不能走
                if (tempx < 0 || tempx >= n || tempy < 0 || tempy >= n) continue;
                if (maze[tempx][tempy] == '#') continue;
                
                node new_node =
                    node(tempx, tempy, path.front().key, path.front().step + 1,
                         path.front().snake_state);
                // 成功
                if (maze[tempx][tempy] == 'T' && new_node.key == m) {
                    finish = true;
                    ans.push_back(new_node.step);
                }
                // 改变钥匙状态
                if (maze[tempx][tempy] >= '1' && maze[tempx][tempy] <= '9') {
                    if (maze[tempx][tempy] - '0' == new_node.key + 1)
                        new_node.key++;
                }
                // 改变蛇状态
                if (maze[tempx][tempy] == 'S') {
                    int num = snake[make_pair(tempx, tempy)];
                    // 蛇还活着就打死
                    if (new_node.snake_state & (1 << num)) {
                        new_node.step++;
                        new_node.snake_state &= ~(1 << num);
                    }
                }
                if (visited[new_node.x][new_node.y][new_node.key][new_node.snake_state])
                    continue;
                path.push(new_node); 
                visited[new_node.x][new_node.y][new_node.key][new_node.snake_state] = 1;
            }
            path.pop();
        }
        if (!finish) cout << "impossible" << endl;
        else {
            int MIN = numeric_limits<int>::max();
            for(int i: ans){
                MIN = min(MIN, i);
            }
            cout << MIN << endl;
        }
    }
    system("pause");
    return 0;
}
