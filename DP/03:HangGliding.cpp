/*
 * @Author: Xia Hanyu
 * @Date:   2020-05-13 17:31:47
 * @Last Modified by:   Xia Hanyu
 * @Last Modified time: 2020-05-13 17:48:03
 */
#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
    int t, n, h[101];
    cin >> t;
    while(t--){
        cin >> n;
        for(int i = 0; i < n; ++i)
            cin >> h[i];
        int ans = 0;
        int dp1[101] = {0};
        for(int i = 0; i < n; ++i){
            dp1[i] = 1;
            for(int j = 0; j < i; ++j){
                if(h[j] < h[i])
                    dp1[i] = max(dp1[i], dp1[j] + 1);
            }
            ans = max(ans, dp1[i]);
        }

        int dp2[101] = {0};
        for(int i = n - 1; i >= 0; --i){
            dp2[i] = 1;
            for(int j = n - 1; j > i; --j){
                if(h[j] < h[i])
                    dp2[i] = max(dp2[i], dp2[j] + 1);
            }
            ans = max(ans, dp2[i]);
        }
        cout << ans << endl;
    }
    system("pause");
    return 0;
}

