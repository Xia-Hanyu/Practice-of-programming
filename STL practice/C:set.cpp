#include<iostream>
#include<set>
#include<string>
#include<iterator>
using namespace std;

int main()
{
    set<int> s;
    multiset<int> muls;
    int n; cin >> n;
    string op;
    while(n--)
    {
        cin >> op;
        if(op == "add"){
            int num; cin >> num;
            s.insert(num), muls.insert(num);
            cout << muls.count(num) << endl;
        }
        else if(op == "del"){
            int num; cin >> num;
            cout << muls.count(num) << endl;
            muls.erase(muls.lower_bound(num), muls.upper_bound(num));
        }
        else if(op == "ask"){
            int num; cin >> num;
            if(s.find(num) != s.end()){
                cout << "1 "; 
            }else{
                cout <<"0 ";
            }
            cout << muls.count(num) << endl;
        }
    }
    system("pause");
    return 0;
}
