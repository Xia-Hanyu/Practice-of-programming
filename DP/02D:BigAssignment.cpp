/*
 * @Author: Xia Hanyu
 * @Date:   2020-05-20 17:52:02
 * @Last Modified by:   Xia Hanyu
 * @Last Modified Time: 2020-05-20 18:33:56
 */
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <iterator>
#include <limits>

using namespace std;

int t, n;
int ddl[20], Time[20];
string course[20];
vector<string> ans, path;
int MIN = numeric_limits<int>::max();
int book[20] = {0};

void solve(int x, int cur, int score){
    if(x == n + 1){
        if(MIN > score){
            MIN = score;
            ans.clear();
            for(auto i = path.begin(); i != path.end(); ++i)
                ans.push_back(*i);
        }
        return;
    }
    if(score > MIN) return;
    for(int i = 0; i < n; ++i){
        if(!book[i]){
            book[i] = 1;
            path.push_back(course[i]);
            solve(x + 1, cur + Time[i], (cur + Time[i] > ddl[i] ? score + cur + Time[i] - ddl[i] : score));
            book[i] = 0;
            path.pop_back();
        }
    }
    return;
}

int main(int argc, char const *argv[])
{
    
    cin >> t;
    while(t--){
        memset(book, 0, sizeof(book));
        ans.clear(), path.clear();
        MIN = numeric_limits<int>::max();
        cin >> n;
        for(int i = 0; i < n; ++i)  
            cin >> course[i] >> ddl[i] >> Time[i];
        solve(1, 0, 0);
        cout << MIN << endl;
        copy(ans.begin(), ans.end(), ostream_iterator<string>(cout, "\n"));
    }
    system("pause");
    return 0;
}

