/*
 * @Author: Xia Hanyu
 * @Date:   2020-05-20 16:41:28
 * @Last Modified by:   Xia Hanyu
 * @Last Modified time: 2020-05-20 17:06:59
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int kinds[10010] = {0}; // kinds[i]总价值为i时组合数
int sub_kinds[200][10010] = {0}; // sub_kinds[i][j]缺少i号硬币总价值为j时组合数
int coins[200];
int n, x;
vector<int> ans;

int main(int argc, char const *argv[])
{
    cin >> n >> x;
    kinds[0] = 1;
    for(int i = 0; i < n; ++i) {
        cin >> coins[i];
        for(int j = x; j >= coins[i]; --j)
            kinds[j] += kinds[j - coins[i]];
    }

    for(int i = 0; i < n; ++i){
        sub_kinds[i][0] = 1;
        for(int j = 1; j <= x; ++j){
            if(j >= coins[i]){
                sub_kinds[i][j] = kinds[j] - sub_kinds[i][j - coins[i]];
            }else{
                sub_kinds[i][j] = kinds[j];
            }
        }
        if(sub_kinds[i][x] == 0){
            ans.push_back(coins[i]);
        }   
    }
    cout << ans.size() << endl;
    if(ans.size() == 0) cout << endl;
    else{
        sort(ans.begin(), ans.end());
        copy(ans.begin(), ans.end(), ostream_iterator<int>(cout, " "));
    }
    system("pause");
    return 0;
}

