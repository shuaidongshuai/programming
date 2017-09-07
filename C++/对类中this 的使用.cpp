#include<iostream>
using namespace std;
class dong
{
	int a,b;
	char c;
public:
	dong()
	{
	a=0;b=0;c='0';
	}
	dong(int q,int w,char e)
	{
	a=q;b=w;c=e;
	}
	void print()
	{
		cout<<a<<","<<b<<","<<c<<endl;
	}
	void copy(dong &x);
};
void dong::copy (dong &x)
{
	*this=x;		//就这一步  把 x  里面的类  复制到 this中也就是这个类中 
}
int main()
{
	dong one(10,20,'A'),two;
	one.print ();
	two.print ();
	two.copy (one);		//复制one 已经定义的类 
	two.print() ;
}
