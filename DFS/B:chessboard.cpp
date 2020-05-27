/*
 * @Author: Xia Hanyu
 * @Date:   2020-05-26 20:01:56
 * @Last Modified by:   Xia Hanyu
 * @Last Modified time: 2020-05-27 11:20:30
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

char map[10][10];
int n, k;
long long ans = 0;
int col[10];
void dfs(int x, int num) {
    if (num == k) {
        ans++;
        return;
    }
    if(x > n) return;
    for (int j = 0; j < n; ++j) {
        if (map[x][j] == '#' && !col[j]) {
            col[j] = 1;
            dfs(x + 1, num + 1);
            col[j] = 0;
        }
    }
    dfs(x + 1, num);
}

int main(int argc, char const *argv[]) {
    while (scanf("%d %d", &n, &k) && n != -1) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) scanf(" %c", &map[i][j]);
        memset(col, 0, sizeof(col));
        ans = 0;
        dfs(0, 0);
        cout << ans << '\n';
    }
    system("pause");
    return 0;
}
