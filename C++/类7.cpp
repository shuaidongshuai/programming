#include<iostream>
using namespace std;
class crect;
class cpoint 
{
public:
	void dong(crect &r,int w);	//不能写在public 外面 
	int a,b;
	cpoint(int c,int d)
	{
		a=c;b=d;
	}
	void get()
	{
		cout<<a<<"  "<<b<<endl;
	}
};
class crect
{
friend void cpoint::dong(crect &r,int w);
public:
	crect(int x,int y)
	{
		x1=x;x2=y;
	}
	void get()		//不能写在public外面 
	{
		cout<<x1<<" "<<x2<<endl; 
	}
	private:
	int x1,x2;
};
void cpoint::dong(crect &r,int w)
{
	a+=w;
	b+=w;
	r.x1+=w;
	r.x2+=w;
}
int main()
{
	cpoint q(2,2);
	crect e(10,10);
	q.get();
	e.get();
	q.dong(e,1);
	q.get();
	e.get();
	return 0;
}
