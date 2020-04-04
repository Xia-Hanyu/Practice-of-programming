/*看起来还行的解法，但是TLE

#include<iostream>
#include<memory>
#include<cstring>
using namespace std;

const int N = 3;
int clocks[N][N];
int ans_stack[9];
int top = 0;
bool solved = false;

#define A 0,0  
#define B 0,1
#define C 0,2
#define D 1,0
#define E 1,1
#define F 1,2
#define G 2,0
#define H 2,1
#define I 2,2

inline void move(int i, int j)
{
	clocks[i][j] = (clocks[i][j] + 1) % 4;
}

inline void anti_move(int i, int j)
{
	if(clocks[i][j] == 0){
		clocks[i][j] = 3;
	}else{
		clocks[i][j] -= 1;
	}
}

inline void operate(int num) 
{
	switch(num)
	{
		case 1: move(A); move(B); move(D); move(E); break;
		case 2: move(A); move(B); move(C); break;
		case 3: move(B); move(C); move(E); move(F); break;
		case 4: move(A); move(D); move(G); break;
		case 5: move(B); move(D); move(E); move(F); move(H); break;
		case 6: move(C); move(F); move(I); break;
		case 7: move(D); move(E); move(G); move(H); break;
		case 8: move(G); move(H); move(I); break;
		case 9: move(E); move(F); move(H); move(I); break;
	}
}

inline void anti_operate(int num)
{
	switch(num)
	{
		case 1: anti_move(A); anti_move(B); anti_move(D); anti_move(E); break;
		case 2: anti_move(A); anti_move(B); anti_move(C); break;
		case 3: anti_move(B); anti_move(C); anti_move(E); anti_move(F); break;
		case 4: anti_move(A); anti_move(D); anti_move(G); break;
		case 5: anti_move(B); anti_move(D); anti_move(E); anti_move(F); anti_move(H); break;
		case 6: anti_move(C); anti_move(F); anti_move(I); break;
		case 7: anti_move(D); anti_move(E); anti_move(G); anti_move(H); break;
		case 8: anti_move(G); anti_move(H); anti_move(I); break;
		case 9: anti_move(E); anti_move(F); anti_move(H); anti_move(I); break;
	}
}

inline bool found()
{
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){
			if(clocks[i][j] != 0)
				return false;
		}
	}
	return true;
}

void Try(int op_num)
{
	if(solved)
		return;
	if(op_num == 0){
		if(found()){
			solved = true;
			for(int i = 0; i < top; ++i)
				cout << ans_stack[i] << " ";
		}
		return;
	}
	for(int i = 1; i <= 9; ++i){
		operate(i);
		ans_stack[top++] = i;
		Try(op_num - 1);
		anti_operate(i);
		top--;
	}
	return;
}

int main()
{
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){
			cin >> clocks[i][j];
		}
	}
	for(int i = 1; i <= 9; ++i)
		Try(i);
	system("pause");
	return 0;
}
*/

// 以下正解 虽然很丑
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

const int inf = 999999999;

int Clock[10]; 
int op[10]; // 每种操作进行的次数
int ans[10]; 

int main()
{
	int min_cnt = inf;
	for(int i = 1; i <= 9; ++i){
		cin >> Clock[i];
	}
	// 真正的枚举
	// 9循环就nm离谱
	for(op[1] = 0; op[1] < 4; ++op[1])
	for(op[2] = 0; op[2] < 4; ++op[2])
	for(op[3] = 0; op[3] < 4; ++op[3])
	for(op[4] = 0; op[4] < 4; ++op[4])
	for(op[5] = 0; op[5] < 4; ++op[5])
	for(op[6] = 0; op[6] < 4; ++op[6])
	for(op[7] = 0; op[7] < 4; ++op[7])
	for(op[8] = 0; op[8] < 4; ++op[8])
	for(op[9] = 0; op[9] < 4; ++op[9])
	{
		int sum = 0;
        sum += (Clock[1] + op[1] + op[2] + op[4]) % 4; // A
    	sum += (Clock[2] + op[1] + op[2] + op[3] + op[5]) % 4; // B
    	sum += (Clock[3] + op[2] + op[3] + op[6]) % 4; // C
        sum += (Clock[4] + op[1] + op [4] + op[5] + op[7]) % 4; // D
        sum += (Clock[5] + op[1] + op[3] + op[5] + op[7] + op[9]) % 4; // E
        sum += (Clock[6] + op[3] + op[5] + op[6] + op[9]) % 4; // F
        sum += (Clock[7] + op[4] + op[7] + op[8]) % 4; // G
        sum += (Clock[8] + op[5] + op[7] + op[8] + op[9]) % 4; // H
        sum += (Clock[9] + op[6] + op[8] + op[9]) % 4; // I
		if(sum == 0){
			int cnt = 0;
			for(int i = 1; i <= 9; ++i){
				cnt += op[i];
			}
			if(cnt < min_cnt){
				min_cnt = cnt;
				memcpy(ans, op, sizeof(op));
			}
		}
	}
	for(int i = 1; i <= 9; ++i){
		while(ans[i]--)
			cout << i << " ";
	}
	system("pause");
	return 0;
}
