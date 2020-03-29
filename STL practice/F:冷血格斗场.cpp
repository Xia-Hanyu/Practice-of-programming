#include<iostream>
#include<map>
#include<cmath>
#include<algorithm>
using namespace std;

int main()
{
    int n;
    multimap<int, int> all;
    all.insert(make_pair(1000000000, 1));
    scanf("%d", &n);
    int id, strength;
    while(n--)
    {
        scanf("%d %d", &id, &strength);
        auto range = all.equal_range(strength);
        int diff;
        if(all.find(strength) != all.end())
            diff = 0;
        else{
            if(range.first == all.begin()){
            diff = all.begin()->first - strength;
            }else{
                range.first--;
                if(range.second == all.end())
                    diff = strength - range.first->first;
                else
                    diff = min(strength - range.first->first, range.second->first - strength);
            }
        }
        int comp = 9999999999;
        auto n_range = all.equal_range(strength + diff);
        for(auto i = n_range.first; i != n_range.second; ++i){
            if(i->second < comp)
                comp = i->second;
        }
        n_range = all.equal_range(strength - diff);
        for(auto i = n_range.first; i != n_range.second; ++i){
            if(i->second < comp)
                comp = i->second;
        }
        printf("%d %d\n", id, comp);
        all.insert(make_pair(strength, id));
    }
    system("pause");
    return 0;
}
