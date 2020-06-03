/*
 * @Author: Xia Hanyu
 * @Date:   2020-06-02 17:22:35
 * @Last Modified by:   Xia Hanyu
 * @Last Modified time: 2020-06-03 13:07:19
 */
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <queue>
using namespace std;

int maze[5][5];
int visited[5][5] = {0};
int dx[] = {0, -1, 0, 1}, dy[] = {1, 0, -1, 0};
struct node
{
    int x, y, pre;
    node(int x_, int y_, int pre_): x(x_), y(y_), pre(pre_) {}
    node() {}
};


int main(int argc, char const *argv[]) {
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)  
            cin >> maze[i][j];
    
    node que[1000];
    int head = 0, tail = 0;
    que[tail++] = node(0, 0, -1);
    visited[0][0] = 1;
    while(head < tail){
        for(int i = 0; i < 4; ++i){
            int tempx = que[head].x + dx[i], tempy = que[head].y + dy[i];
            if(tempx < 0 || tempx > 4 || tempy < 0 || tempy > 4) continue;
            if(visited[tempx][tempy] || maze[tempx][tempy] == 1) continue;
            visited[tempx][tempy] = 1;
            que[tail++] = node(tempx, tempy, head);
        } 
        if(que[tail - 1].x == 4 && que[tail - 1].y == 4) break;
        head++;
    }
    list<node> ans;
    ans.push_front(que[tail - 1]);
    int previous = que[tail - 1].pre;
    while(previous != -1){
        ans.push_front(que[previous]);
        previous = que[previous].pre;
    }
    for(auto i = ans.begin(); i != ans.end(); ++i){
        printf("(%d, %d)\n", i->x, i->y);
    }
    system("pause");
    return 0;
}
