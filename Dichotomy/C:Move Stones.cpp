#include<iostream>  
#include<cmath>
#include<cstring>
#include<vector>
#include<string>
#include<stdio.h>
#include<sstream>
#include<limits>
using namespace std;

long long L;
int n, m;
long long d[50001];

bool check(long long x) // 最小间距为x是否符合要求
{
    int num = 0, pre = 0;
    for(int i = 1; i <= n; ++i){
        if(d[i] - pre < x){
            num++;
        }else{
            pre = d[i];
        }
    }
    if(L - pre < x) num++;
    return num <= m; // 搬走石头小于x，说明满足条件，最小间距还可以扩大
}

int main()  
{
    cin >> L >> n >> m;
    d[0] = 0;
    // 二分区间为 最小间距-L
    long long l = numeric_limits<long long>::max(), r = L;
    for(int i = 1; i <= n; ++i){
        cin >> d[i];
        l = min(l, d[i] - d[i - 1]);
        r = max(r, d[i] - d[i - 1]);
    }
    // 加上终点情况
    l = min(l, L - d[n]);
    r = max(r, L - d[n]);

    long long ans;
    // 二分
    while(l <= r){
        long long mid = l + (r - l) / 2;
        if(check(mid)){ 
            l = mid + 1;
            ans = mid; // 记录可行答案
        }else{
            r = mid - 1;
        }
    }
    cout << ans;
    system("pause");
    return 0;  
} 
