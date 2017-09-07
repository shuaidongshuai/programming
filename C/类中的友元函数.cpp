#include<iostream>
using namespace std;
class cpoint
{
	friend cpoint inflate(cpoint &pt,int noffset);//声明一个友元函数
public:
	cpoint(int x=0,int y=0)
	{
		xp=x;yp=y;
	}
	void print()
	{
		cout<<"point("<<xp<<","<<yp<<")"<<endl;
	}
private:
	int xp,yp;
};
cpoint inflate(cpoint &pt,int noffset)			//class外部   友元函数的定义
{
	pt.xp +=noffset;							//直接改变私有数据成员
	pt.yp +=noffset;
	return pt;
}
int main()
{
	cpoint a(10,20);
	a.print ();
	inflate(a,3);							//直接调用友元函数
	a.print ();
	return 0;
}
