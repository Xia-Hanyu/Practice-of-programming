/*
 * @Author: Xia Hanyu
 * @Date:   2020-05-20 17:13:31
 * @Last Modified by:   Xia Hanyu
 * @Last Modified time: 2020-05-20 17:41:36
 */
#include <iostream>

using namespace std;

int dp[13000] = {0};

int main(int argc, char const *argv[])
{
    int n, m, w[3500], d[3500];
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) cin >> w[i] >> d[i];

    /**
     * 滚动数组
     * 状态转移方程与之前的i无关，因而dp table不需要二维
     * 对于j 最多用到dp[j - w[i]]因而数组可以开到m
    */
    for(int i = 1; i <= n; ++i){
        for(int j = m; j >= w[i]; --j){
            dp[j] = max(dp[j], dp[j - w[i]] + d[i]);
        }
    }
    cout << dp[m] << endl;
    system("pause");
    return 0;
}

