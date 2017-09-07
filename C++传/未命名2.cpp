#include <iostream>
using namespace std;
struct A
{
    long long _x1;
    char _x2;
    int _x3;
    char _x4[2];
    static int _x5;
};
int A::_x5;

struct B
{
    long long _x1;
    char _x2;
    short _x3;
    char _x4[3];
};

int main()
{
	cout<<sizeof(A)<<endl;
	cout<<sizeof(B)<<endl;
}
