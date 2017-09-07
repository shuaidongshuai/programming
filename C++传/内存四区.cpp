#include <iostream>
using namespace std;

//成员函数，静态函数----在“代码区 ”-------不计入程序体积
//空指针，数据独享，代码共享，不调用，类成员数据，可以调用没有私有数据的代码区函数

//静态区优先于main函数，全局对象，在静态区
//静态变量在静态区，只会初始化一次，求类大小，不计入程序体积。
//类中的const与类成员数据一样 

//类中的非静态数据，与对象位置有关
//函数外的对象，静态区，函数内，栈区，动态分配，堆区
//类中的指针，分配内存一般在堆区//new可以分配在任何一个区

class Dong
{
	int i; 
	static int d; 
	public:
		Dong()
		{
			cout<<"析构"<<endl; 
		}
		//代码区 
		void show()
		{
			cout<<"hello"<<endl;
		}
		static show2()
		{
			cout<<"hello2"<<endl;
		}
}; 
//静态区
Dong* d = new Dong();
Dong dd;

int Dong::d = 0;//静态区 

int main()
{
	Dong* d;
	d->show2();
	
	Dong* dd = new Dong();// dd 在栈区，，，，*dd（指针所指向的对象）在堆区 
	
	cout<<sizeof(Dong)<<endl;//4没有包括 	static int d; 这个变量，，因为 d 放到了 静态区 
	
}
