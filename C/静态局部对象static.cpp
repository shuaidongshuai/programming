#include<iostream>
using namespace std;
int fun()
{
	static int c=0;	//只是一开始给c一个值，不管以后该函数是否被再次调用，c都不会再被重新赋值 
	c++;
	return c;
}
int dong1()
{
	static int c;	//即使不赋初值默认给c赋初值=0；以后就算再次调用该函数也不会对c再次赋初值 
	c++;
	return c;
}
int dong()
{
	int a=5;		//每次调用该函数，都要重新赋值a=5;
	a++;
	return a;
}
int main() 
{
	int i,c,a,b;
	for(i=1;i<=10;i++)
	{
	a=fun();
	b=dong1();
	c=dong();
}
	cout<<a<<"  "<<b<<"   "<<c<<endl;
	return 0;
}
