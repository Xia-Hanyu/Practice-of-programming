#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include<vector>
using namespace std;

bool isprime(int x)
{
    for(int i = 2; i <= sqrt(x); ++i)
        if(x % i == 0)
            return false;
    return true;
}

class worse
{
    public:
    bool operator()(int & a, int & b)
    {
        int a_prime = 0, b_prime = 0;
        for(int i = 2; i <=sqrt(a); ++i){
            if(a % i == 0){
                if(isprime(i)) a_prime++;
                if(isprime(a / i)) a_prime++;
            }  
        }
        for(int i = 2; i <= sqrt(b); ++i){
            if(b % i == 0){
                if(isprime(i)) b_prime++;
                if(isprime(b / i)) b_prime++;
            }
        }
        if(a_prime == b_prime)
            return a > b;
        else
            return a_prime > b_prime;
    }
};

class better
{
    public:
    bool operator()(int & a, int & b)
    {
        int a_prime = 0, b_prime = 0;
        for(int i = 2; i <=sqrt(a); ++i){
            if(a % i == 0){
                if(isprime(i)) a_prime++;
                if(isprime(a / i)) a_prime++;
            }
        }
        for(int i = 2; i <= sqrt(b); ++i){
            if(b % i == 0){
                if(isprime(i)) b_prime++;
                if(isprime(b / i)) b_prime++;
            }
        }
        if(a_prime == b_prime)
            return a < b;
        else
            return a_prime < b_prime;
    }
};

int main() 
{
    // priority_queue 排序方式很迷惑
    priority_queue<int, vector<int>, better> best;
    priority_queue<int, vector<int>, worse> worst;
    int n;
    cin >> n;
    while(n--)
    {
        int num;
        for(int i = 0; i < 10; ++i){
            cin >> num;
            best.push(num); worst.push(num);
        }
        cout << best.top() << " " << worst.top() << endl;
        best.pop(); worst.pop();
    }
    system("pause");
    return 0;
}
