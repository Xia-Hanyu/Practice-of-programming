/*
 * @Author: Xia Hanyu
 * @Date:   2020-04-27 21:54:21
 * @Last Modified by:   Xia Hanyu
 * @Last Modified time: 2020-04-29 16:58:32
 */
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <string>
#include <cstring> 
#include <set>
#include <vector>
#include <limits>
using namespace std;

int h[100][100];
int r, c;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

int solved[100][100] = {0};

int dfs(int x, int y)
{
    if(solved[x][y])
        return solved[x][y];
    solved[x][y] = 1;
    for(int k = 0; k < 4; ++k){
        int tmpx = x + dx[k], tmpy = y + dy[k];
        if(tmpx >= 0 && tmpx < r && tmpy >= 0 && tmpy < c && h[x][y] > h[tmpx][tmpy]){
            solved[x][y] = max(solved[x][y], dfs(tmpx, tmpy) + 1);
        }
    }
    return solved[x][y];
}

int main(int argc, char const *argv[])
{
    cin >> r >> c;
    for(int i = 0; i < r; ++i)
        for(int j = 0; j < c; ++j)
            cin >> h[i][j];
    int ans = 0;
    for(int i = 0; i < r; ++i)
        for(int j = 0; j < c; ++j)
            ans = max(ans, dfs(i, j));
    cout << ans << endl;
    system("pause");
    return 0;
}

