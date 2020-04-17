#include<iostream>  
#include<cmath>
#include<cstring>
#include<vector>
#include<string>
#include<algorithm>
#include<stdio.h>
#include<sstream>
#include<limits>
using namespace std;

int n, m;
int cost[100000];

bool check(int x) // 最大月开销为x时是否满足
{
    int sum = 0, num = 0; // 月开销、月份数
    for(int i = 0; i < n; ++i){
        if(sum + cost[i] <= x){ // 月开销小于x，可以继续添加
            sum += cost[i];
        }else{ // 否则开启一个新月
            num++;
            sum = cost[i];
        }
    }
    return num >= m; // 划分出月份数 >= m 说明x尚可继续增加
}


int main()  
{
    cin >> n >> m;
    int max_cost = 0, total = 0;
    for(int i = 0; i < n; ++i){
        cin >> cost[i];
        total += cost[i];
        if(max_cost < cost[i])
            max_cost = cost[i];
    }
    // 二分区间为最大天开销-总开销
    int l = max_cost, r = total;
    while(l < r){
        int mid = l + (r - l) / 2;
        if(check(mid)){
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    cout << l;
    system("pause");
    return 0;  
} 
