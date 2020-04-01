#include <iostream>
using namespace std;
#include<functional>
template<typename T1, typename T2>
// C++14 直接auto就可以过
function<T2(T2)> f(T1 val1)
{
    return [=](T2 val2){return val2 + val1;};
}

int main()
{
   cout << f<int,int>(7)(9) << endl;   //16
   cout << f<string,string> (" hello!")("world")  <<endl; // world hello!
   cout << f<char,string> ('!')("world") << endl;
   
   system("pause");
   return 0;    //world!
}
