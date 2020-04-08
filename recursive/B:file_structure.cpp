#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

void GetDir(int step) // step 表示处于第几层子目录
{
    char c = cin.peek();
    string file;
    string subdir;
    vector<string> files;
    while(c != '*')
    {
        if(c == ']'){ // 目录结束，输出内容
            cin.get(); cin.get();
            // 文件名
            sort(files.begin(), files.end());
            for(auto i = files.begin(); i != files.end(); ++i){
                for(int j = 1; j <= step; ++j){
                    cout << "|     ";
                }
                cout << *i << endl;
            }
            return;
        }
        // 添加新文件
        if(c == 'f'){
            cin >> file; cin.get();
            files.push_back(file);
        }   
        // 添加子目录
        if(c == 'd'){
            cin >> subdir; cin.get();
            for(int i = 1; i <= step + 1; ++i)
                cout << "|     ";
            cout << subdir << endl;
            GetDir(step + 1);
        }
        c = cin.peek();
    }
    // * 输出根目录文件
    cin.get(); cin.get();
    sort(files.begin(), files.end());
    for(auto i = files.begin(); i != files.end(); ++i){
        for(int j = 1; j <= step; ++j){
            cout << "|     ";
        }
        cout << *i << endl;
    }
    cout << endl;
    return;
}

int main()
{
    int cnt = 0;
    while(cin.peek() != '#')
    {
        cnt++;
        cout << "DATA SET " << cnt << ":" << endl
             << "ROOT" << endl;
        GetDir(0);
    }
    system("pause");
    return 0;
}
