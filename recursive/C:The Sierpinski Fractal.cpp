#include<iostream>
#include<cstring>
using namespace std;

const int MAX = 4000;
char map[MAX][MAX];

void draw(int depth, int x, int y)
{
    if(depth == 1){
        map[x][y + 1] = '/';
        map[x][y + 2] = '\\';
        map[x + 1][y] = '/';
        map[x + 1][y + 1] = '_';
        map[x + 1][y + 2] = '_';
        map[x + 1][y + 3] = '\\';
    }else{
        int k = (1 << (depth - 1));
        draw(depth - 1, x, y + k);
        draw(depth - 1, x + k, y);
        draw(depth - 1, x + k, y + 2 * k);
    }
    return;
}

int main()
{
    int n;
    while(cin >> n && n != 0)
    {
        memset(map, ' ', sizeof(map));
        draw(n, 1, 1);
        for(int i = 1; i <= (1 << n); ++i){
            for(int j = 1; j <= (2 << n); ++j){
                cout << map[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
    system("pause");
    return 0;
}
