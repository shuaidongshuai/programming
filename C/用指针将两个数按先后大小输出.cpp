#include<iostream>
using namespace std;
int main()
{
	int t,a=2,b=3,*p,*p1=&a,*p2=&b;
	cout<<"a="<<*p1<<"b="<<*p2<<endl;
	p=p2;		//这种调换是调换p1与p2，，，a还是二，b还是三 
	p2=p1;
	p1=p;
	cout<<"a="<<*p1<<"b="<<*p2<<endl;
	t=*p1;		//这种调换是直接调换a与b的值； a变为三 
	*p1=*p2;
	*p2=t;
	cout<<"a="<<*p<<"b="<<*p2;
}
