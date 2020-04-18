#include<iostream>  
#include<cmath>
#include<cstring>
#include<vector>
#include<string>
#include<stdio.h>
#include<sstream>
#include<limits>
#include<iomanip>
#include<algorithm>
using namespace std; 

const int N_MAX = 100000;
int N, F;
int radius[N_MAX];
const double pi = acos(-1);

bool check(double x) // 检查每块面积为x时是否满足
{
    int num = 0;
    for(int i = 0; i < N; ++i){
        num += int(pi * radius[i] * radius[i] / x);
    }
    return num >= F + 1;
}

int main()  
{
    cin >> N >> F;
    double l = 0, r = 0;
    for(int i = 0; i < N; ++i){
        cin >> radius[i];
        r = max(r, pi * radius[i] * radius[i]);
    }
    double ans;
    const double step = 0.00001; // 我以为这样写会超时
    while(l <= r){
        double mid = l + (r - l) / 2;
        if(check(mid)){
            l = mid + step;
            ans = mid;
        }else{
            r = mid - step;
        }
    }
    cout << fixed << setprecision(3) << ans;
    system("pause");
    return 0;  
} 
