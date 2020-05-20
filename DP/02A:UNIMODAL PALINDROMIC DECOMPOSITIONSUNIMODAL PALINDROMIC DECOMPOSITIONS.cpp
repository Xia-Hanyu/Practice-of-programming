/*
 * @Author: Xia Hanyu
 * @Date:   2020-05-20 16:15:56
 * @Last Modified by:   Xia Hanyu
 * @Last Modified time: 2020-05-20 16:18:46
 */

#include <iostream>
#include <string>
using namespace std;

long long dp[255][255] = {0};
/**
 * dp[i][j] 表示和为i的序列最小值至少为j的组合种数
*/

int main() {
    int n, i, j;
    for (i = 0; i < 255; i++)
        for (j = 0; j < 255; j++)
            if (i == 0 || i >= j) dp[i][j] = 1;
    for (i = 1; i < 255; i++)
        for (j = i / 2; j >= 1; j--)
            dp[i][j] = dp[i - 2 * j][j] + dp[i][j + 1]; // 可以选用j + 不可以选用j
    while (cin >> n && n != 0) {
        cout << n << " " << dp[n][1] << endl;
    }
    return 0; 
}
