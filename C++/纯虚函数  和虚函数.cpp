#include<iostream>
using namespace std;
class cshape
{
public:
	virtual float area(){return 0;}			//这是虚函数   把{return 0}变成 =0   就成了纯虚函数 
};
class ct:public cshape
{
public:
	ct(float h,float w)
	{
		H=h;W=w;
	}
	float area()
	{
		return H*W*0.5;
	}
private:
	float H,W;
};
class cc:public cshape
{
public:
	cc(float r)
	{
		R=r;
	}
	float area()
	{
		return 3.14*R*R;
	}
private:
	float R;
};
int main()
{
	cshape *p,*s;
	p=new ct(3,4);
	cout<<p->area()<<endl;
	s=new cc(5);
	cout<<s->area ()<<endl;
	return 0;
}
