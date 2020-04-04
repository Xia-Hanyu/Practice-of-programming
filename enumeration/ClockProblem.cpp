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
