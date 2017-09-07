#include <iostream>
using namespace std;

int main()
{
	long long a = 10;
	long long *b = &a;
	long long &c = a;
	cout<<sizeof(a)<<endl;
	cout<<sizeof(b)<<endl;
	cout<<sizeof(c)<<endl;
}
