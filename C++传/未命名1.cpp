#include <iostream>
using namespace std;  

int main()
{
	int a = 0;
	int *p = &a;
	cout<<p<<"\t"<<&a<<endl;
	cout<<p+1<<"\t"<<&a + 1<<endl;
	cout<<p+2<<"\t"<<&a + 2<<endl;
}
