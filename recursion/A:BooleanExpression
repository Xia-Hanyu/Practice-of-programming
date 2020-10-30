#include<iostream>  
#include<cmath>
#include<cstring>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

bool expression();
bool factor();

bool factor()
{
    bool result;
    while(cin.peek() == ' '){
        cin.get();
    }
    switch(cin.peek()){
        case 'V': cin.get(); result = true; break;
        case 'F': cin.get(); result = false; break;
        case '!': cin.get(); result = !factor(); break;
        case '(': cin.get(); result = expression(); cin.get();
    }
    return result;
}

bool expression() // 表达式由factor连接而来
{
    bool result = factor(); 
    bool more = true;
    while(more){
		char op = cin.peek();
		if(op == ' '){
            cin.get();
        }else if(op == '|' || op == '&'){
			cin.get();	
			bool value = factor();
			if(op == '|'){
                result |= value;
            }else{
                result &= value;
            }
		}else{ // 换行符或EOF
            more = false;
        }
	}
    return result;
}

int main()  
{ 
    int num = 0;
    while(cin.peek() != EOF){
        num++;
        cout << "Expression " << num << ": ";
        if(expression()){
            cout << "V" << endl;
        }else{
            cout << "F" << endl;
        }
        cin.get(); // 删除换行符
    }
    system("pause");
    return 0;  
}  
