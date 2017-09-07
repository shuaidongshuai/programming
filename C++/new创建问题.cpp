#include<iostream>
using namespace std;


class D{
	static int i;
	static int j;
	public:
		D()
		{
			cout<<"构造"<<i++<<endl;
		}
		~D()
		{
			cout<<"析构"<<j++<<endl;
		}
};
int D::i = 1;
int D::j = 1;


int main()
{
	//定位new
	char buffer[1024] ;//在栈上
	char *p = new (buffer) char[100];//在buffer上的内存中开辟100char   其实相当于没有开辟内存
	
	int *q = new int;
	int *q2 = new int;
	int *qq = new (q) int(10);
	cout<<q<<endl;				//0x8d14e0
	cout<<qq<<endl;				//0x8d14e0  地址一样 
	cout<<q2<<endl;				//0x8d1500
	
	int *d = (int*) operator new(sizeof(int));//malloc开辟内存
	cout<<*d<<endl;				//3873248		//这里只开辟内存，没有初始化 
	int *dd = new (d) int(10);
	cout<<*d<<endl;				//10			//初始化
	cout<<*dd<<endl;
	
	*d = 99;// d 与 dd 指向同一片内存 
	cout<<*d<<endl;				//99
	cout<<*dd<<endl;			//99
 } 

int main4()
{
	//在堆上开辟常量
	const int *p = new const int(10);
	//在堆上开辟常量数组 
	//const int *q = new const int[10];
 } 
int main3()
{
	//怎么判断是否new成功  2
	int *p = new (nothrow) int(10);			//加上 nothrow关键字就不会抛异常，和 malloc一样了 
	if(p == NULL)
	{
		cout<<"没有new成功"<<endl;
	}
	cout<<"new成功"<<endl;
 } 
int main2()
{
	//怎么判断是否new成功
	try										//malloc 是通过返回值是否为NULL 来判断，new是通过抛异常 
	{
		int *p = new int(10);	
	}
	catch(const bad_alloc &err)
	{
		cout<<"没有new成功"<<endl;
	}
	cout<<"new成功"<<endl;
 } 
int main1()
{
	D **p = new D*[4];
	//创建二维数组 
	for(int i = 0;i<4;i++)
	{
		p[i] = new D[2];
	}
	//释放
	 for(int i = 0;i<4;i++)
	{
		delete[] p[i];
	}
	delete[] p;
	
}
