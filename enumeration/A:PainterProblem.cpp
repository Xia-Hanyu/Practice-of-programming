/**
 * 画家问题 实际上是熄灯问题
 * 位运算实现布尔矩阵运算
 * 时间、空间都很节省
*/

#include<iostream>
#include<memory>
#include<cstring>
using namespace std;

const int inf = 999999999;
const int MAX_N = 16;

int N;
enum{yellow = 0, white = 1};
int OriColors[MAX_N];
int colors[MAX_N];
int paints[MAX_N];

int GetBit(int num, int i)
{
	return (num >> i) & 1;
}

void SetBit(int & num, int i, int val)
{
	if(val){
		num |= (1 << i);
	}else{
		num &= ~(1 << i);
	}
}

void FlipBit(int & num, int i)
{
	num ^= (1 << i);
}

int GetResult()
{
	int result = 0;
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){
			result += GetBit(paints[i], j);
		}
	}
	return result;
}

int main()
{
	int ans = inf;
	cin >> N;
	memset(OriColors, 0, sizeof(OriColors));
	// 输入初始颜色
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){
			char c;
			cin >> c;
			switch (c){
				case 'w': SetBit(OriColors[i], j, white); break;
				case 'y': SetBit(OriColors[i], j, yellow); break;
			}
		}
	}
	// 枚举第一行
	int MAX = 1 << N;
	for(int n = 0; n < MAX; ++n){
		memset(paints, 0, sizeof(paints));
		memcpy(colors, OriColors, sizeof(OriColors));
		int switches = n;
		for(int i = 0; i < N; ++i){
			paints[i] = switches;
			// 改变本行状态
			for(int j = 0; j < N; ++j){
				if(GetBit(switches, j)){
					FlipBit(colors[i], j);
					if(j > 0) 
						FlipBit(colors[i], j - 1);
					if(j < N - 1) 
						FlipBit(colors[i], j + 1);
				}
			}
			if(i < N - 1)
				colors[i + 1] ^= switches;
			// 下一行涂色方案取决于本行状态
			switches = colors[i];
		}
		if(colors[N - 1] == 0){ // 最后一行全为yellow, 是一个解
			ans = min(ans, GetResult());
		}
	}
	if(ans == inf){
		cout << "inf" << endl;
	}else{
		cout << ans << endl;
	}
	system("pause");
	return 0;
}
