#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
using namespace std;
// 全部使用scanf printf可以AC， 使用 cin cout会TLE

int main() 
{
    map<int, int> all;
    all.insert(make_pair(1000000000, 1));
    int n;
    scanf("%d", &n);
    while (n--)
    {
        int id, strength;
        scanf("%d %d", &id, &strength);
        auto range = all.equal_range(strength);
        int result;
        if (range.first == all.begin()) {
            result = all.begin()->second;
        }else{
            range.first--;
            if(range.second == all.end())
                result = range.first->second;
            else
                result = strength - range.first->first <= range.second->first - strength ? range.first->second : range.second->second;
        }
        printf("%d %d\n", id, result);
        all.insert(make_pair(strength, id));
    }
    system("pause");
    return 0;
}
