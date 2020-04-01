#include <iostream>
using namespace std;
#include<functional>
template<typename T1, typename T2, typename T3>
function<T3(T3)> combine(T1 & fn1, T2 & fn2)
{
    return [&](T3 x){
        T3 temp = fn1(x) + fn2(x);
        return fn1(temp);
    };
}

int main()
{
    auto Square = [] (double a) { return a * a; };
    auto Inc = [] (double a) { return a + 1; };
    cout << combine<decltype(Square),decltype(Inc),int>(Square,Inc)(3) << endl;
    cout << combine<decltype(Inc),decltype(Square),double>(Inc,Square)(2.5) << endl;
    system("pause");
    return 0;
}
