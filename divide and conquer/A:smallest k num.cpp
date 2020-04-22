/*
 * @Author: Xia Hanyu
 * @Date:   2020-04-21 19:01:54
 * @Last Modified by:   Xia Hanyu
 * @Last Modified time: 2020-04-22 15:39:03
 */
#include <iostream>
#include <algorithm>

using namespace std;

int n, k, num[100000];

int main(int argc, char const *argv[])
{
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> num[i];
    }
    cin >> k;
    sort(num, num + n, greater<int>());
    for(int i = 0; i < k; ++i){
        cout << num[i] << endl;
    }
    system("pause");
    return 0;
}
