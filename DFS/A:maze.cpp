/*
 * @Author: Xia Hanyu
 * @Date:   2020-05-26 20:01:56
 * @Last Modified by:   Xia Hanyu
 * @Last Modified time: 2020-05-27 10:26:12
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

struct node{
    int x, y;
};

vector<node> path;
vector<node> ans;
int minstep = numeric_limits<int>::max();
int map[5][5];
int book[5][5] = {0};
int dx[4] = {0, -1, 0, 1}, dy[4] = {1, 0, -1, 0};

void dfs(int x, int y){
    if(x == 4 && y == 4){
        if(path.size() <= minstep){
            ans = path;
            minstep = path.size();
            return;
        }
    }
    for(int i = 0; i < 4; ++i){
        int tempx = x + dx[i], tempy = y + dy[i];
        if(tempx < 0 || tempx > 4 || tempy < 0 || tempy > 4) continue;
        if(!book[tempx][tempy] && map[tempx][tempy] == 0){
            book[tempx][tempy] = 1;
            node temp;
            temp.x = tempx, temp.y = tempy;
            path.push_back(temp);
            dfs(tempx, tempy);
            path.pop_back();
            book[tempx][tempy] = 0;
        }
    }
}

int main(int argc, char const *argv[])
{
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            cin >> map[i][j];
    book[0][0] = 1;
    dfs(0, 0);
    cout << "(0, 0)" << endl;
    for(node i: ans){
        cout << "(" << i.x << ", " << i.y << ")" << endl;
    }
    system("pause");
    return 0;
}

