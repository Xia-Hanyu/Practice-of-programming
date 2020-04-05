#include<iostream>
#include<string>
using namespace std;

const int inf = 999999999;
void Flip(string & s, int i)
{
	s[i] = (s[i] == '1') ? '0' : '1';
	if(i > 0)
		s[i - 1] = (s[i - 1] == '1') ? '0' : '1';
	if(i < s.size() - 1)
		s[i + 1] = (s[i + 1] == '1') ? '0' : '1';
}

int main()
{
	int ans = inf;
	string s1, s2, temp;
	cin >> s1 >> s2;
	for(int i = 0; i < 2; ++i){
		temp = s1;
		if(i == 0){// 首位按下
			int cnt = 1;
			Flip(temp, 0);
			for(int i = 1; i < temp.size(); ++i){
				if(temp[i - 1] != s2[i - 1]){
					Flip(temp, i);
					cnt++;
				}
			}
			if(temp == s2)
				ans = min(ans, cnt);
		}else{ // 首位不按
			int cnt = 0;
			for(int i = 1; i < temp.size(); ++i){
				if(temp[i - 1] != s2[i - 1]){
					Flip(temp, i);
					cnt++;
				}
			}
			if(temp == s2)
				ans = min(ans, cnt);
		}
	}
	if(ans == inf){
		cout << "impossible" << endl;
	}else{
		cout << ans << endl;
	}
	system("pause");
	return 0;
}
