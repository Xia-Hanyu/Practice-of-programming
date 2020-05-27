/*
 * @Author: Xia Hanyu
 * @Date:   2020-05-27 11:24:21
 * @Last Modified by:   Xia Hanyu
 * @Last Modified time: 2020-05-27 19:42:34
 */
#include <iostream>
#include <limits>
using namespace std;

/**
 * 状态压缩 使用int位储存已经走过的状态
*/

const int INF = 0x3f3f3f;
int map[20][20];
int n;
int book[20] = {0};
int dp[1 << 17][17]; // 记录state状态下当前处于island的情况下的花费
int ans = INF;

void dfs(int state, int island, int sum, int num) {
    if (num == n - 1 && island != n) {
        sum += map[island][n];
        ans = min(ans, sum);
        return;
    }
    for (int i = 2; i < n; ++i) {
        if (!book[i]) {
            int newstate = state | (1 << (i - 1));
            if (island == 1) {
                dp[newstate][i] = map[island][i];
                book[i] = 1;
                dfs(newstate, i, sum + map[island][i], num + 1);
                book[i] = 0;
            } else {
                if (dp[state][island] + map[island][i] >= dp[newstate][i])
                    continue; // 剪枝 这里写 > 就会1200ms, >= 就是200ms, 就离谱
                dp[newstate][i] = map[island][i] + dp[state][island];
                book[i] = 1;
                dfs(newstate, i, sum + map[island][i], num + 1);
                book[i] = 0;
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) cin >> map[i][j];
    for (int i = 0; i < (1 << 17); ++i)
        for (int j = 0; j < 17; ++j) {
            dp[i][j] = INF;
        }
    dfs(1, 1, 0, 1);
    cout << ans << endl;
    system("pause");
    return 0;
}
