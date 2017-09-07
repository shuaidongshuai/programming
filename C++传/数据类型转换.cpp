#include <iostream>
#include <string>
using namespace std;

//dynamic_cast能够应用于指针转换。
//子类指针转换成父类指针
class A
{
	public:
		void run()
		{
			cout<<"A"<<endl;
		}
};
class B:public A
{
	public:
		void run()
		{
			cout<<"B"<<endl;
		}
};
int main0()
{
	B* b = new B;
	b->run();
	A* a = b;
	a->run();
	dynamic_cast<A*>(b)->run();
}

int main1()
{
	//printf不会自动处理数据类型	
	//printf("%d",10.2);
	//printf("%f",1); 
	
//	Static_cast可以转换相关联的类，可以从子类转换成父类。也能从父类转向子类，但是如果转换的父类指针（或者父类引用）所指向的对象是完整的，
//	那么是没有问题；但是如果所指向的对象并不完整，那么会出现runtime错误。
//	Static_cast相对于dynamic_cast而言，除了能转换指针和引用，还能应用于任何能够隐式转换的情况。

	printf("%d",static_cast<int>(10.2));
	
}
int main2()
{
//	reinterpret_cast
//（1）   Int和指针之间的相互转换；
//（2）   无关联类指针之间的转换；
//（3）   函数指针之间的转换
	int *pint = new int(2);
	char *pchar = reinterpret_cast<char*>(pint);
	
	for(int i = 0;i<4;i++)
	{
		cout<<*(pint + i)<<"   "<<reinterpret_cast<void*>(pint + i)<<endl;
	}
	cout<<endl;
	for(int i = 0;i<4;i++)
	{
		cout<<static_cast<int>(*(pchar + i))<<"   "<<reinterpret_cast<void*>(pchar + i)<<endl;
	}
}
int main()
{
//	const_cast如它的名字，它是去除修饰在对象上的const和volatile。
	int a = 47;
	const int* i = &a;
	int* c = const_cast<int*>(i);
	cout<<*c<<endl;
}

