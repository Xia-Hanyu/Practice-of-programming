/*
 * @Author: Xia Hanyu
 * @Date:   2020-04-21 19:01:54
 * @Last Modified by:   Xia Hanyu
 * @Last Modified time: 2020-04-22 16:32:03
 * 
 * 归并排序加一步
 */
#include <iostream>
#include <algorithm>

using namespace std;

int n, num[100000], temp[100000];

long long MergeSort(int begin, int end)
{
    if(begin >= end)
        return 0;
    long long ans = 0;
    int mid = begin + (end - begin) / 2;
    ans += MergeSort(begin, mid);
    ans += MergeSort(mid + 1, end);
    int i = begin, j = mid + 1, k = begin;
    while(i <= mid && j <= end){
        if(num[i] < num[j]){
            temp[k++] = num[i++];
        }else{
            ans += mid - i + 1;
            temp[k++] = num[j++];
        }
    }
    while(i <= mid) temp[k++] = num[i++];
    while(j <= end) temp[k++] = num[j++];
    for(int m = begin; m <= end; ++m){
        num[m] = temp[m];
    }
    return ans;
}

int main(int argc, char const *argv[])
{
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> num[i];
    }
    cout << MergeSort(0, n - 1);
    system("pause");
    return 0;
}

