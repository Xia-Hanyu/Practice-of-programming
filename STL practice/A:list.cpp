#include<iostream>
#include<list>
#include<string>
#include<iterator>
using namespace std;

int main()
{
    list<int> * all[10000] = {NULL};
    int n;
    cin >> n;
    string op;
    while(n--)
    {
        cin >> op;
        if(op == "new"){
            int id;
            cin >> id;
            all[id] = new list<int>;
        }
        else if(op == "add"){
            int id, num;
            cin >> id >> num;
            all[id]->push_back(num);
        }
        else if(op == "merge"){
            int id1, id2;
            cin >> id1 >> id2;
            if(id1 != id2){
                all[id1]->sort(), all[id2]->sort();
                all[id1]->merge(*(all[id2]));
            }
        }
        else if(op == "unique"){
            int id;
            cin >> id;
            all[id]->sort();
            all[id]->unique();
        }
        else if(op == "out"){
            int id;
            cin >> id;
            if(all[id]->size()){
                all[id]->sort();
                cout << all[id]->front();
                auto i = all[id]->begin(); ++i;
                for(; i != all[id]->end(); ++i)
                    cout << " " << *i;
                cout << endl;
            }else{
                cout << endl;
            }
        }
    }
    for(int i = 0; i < 10000; ++i)
        delete all[i];
    system("pause");
    return 0;
}
