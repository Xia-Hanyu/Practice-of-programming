#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
    multimap<int, int> all;
    multimap<int, int>::iterator cur; // 当前存入的数据的迭代器
    all.insert(make_pair(1000000000, 1));
	int n, id, strength;
    cin >> n;
    while(n--)
    {
        cin >> id >> strength;
        cur = all.insert(make_pair(strength, id));
        if(cur == all.begin()){
            cout << id << " " << (++cur)->second << endl;
        }
        else if((++cur) == all.end()){ // 新选手力量最大
            --cur; // 回到当前
            cout << id << " " << (--cur)->second << endl; 
        }
        else{
            auto lower = --cur; ++cur;
            auto higher = ++cur; --cur;
            if(cur->first - lower->first <= higher->first - cur->first)
                cout << id << " " << lower->second << endl;
            else
                cout << id << " " << higher->second << endl;
        }
    }
	system("pause");
	return 0;
}
