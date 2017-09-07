#include <iostream>
using namespace std;

class A{
public:
	long a; 
};
class B : public A{
public:
	long b; 
};

void test(A* data,int i)
{
	data[i].a = 2;			//相当于  data地址 + 4 * i;	//第一次改的就是 data + 4 上long 类型 的值 = 2  第二次改的就是   data + 4 * i 上的值  只修改四次 
}

//我们来看一下内存分布
int main()
{
	B data[4];
	for(int i = 0;i<4;i++)
	{
		data[i].a = 1;
		data[i].b = 2;
	}
	for(int i = 0;i<8;i++)
		cout<<*((long *)(data) + i)<<"\t";//		1       2       1       2       1       2       1       2		看的出来a放在b的前面 
} 

// 错答案： 2 1 2 1 2 1 2 1 
int main1()
{
	cout<<sizeof(long)<<endl;
	cout<<sizeof(A)<<endl;
	cout<<sizeof(B)<<endl;
	
	B data[4];
	for(int i = 0;i<4;i++)
	{
		data[i].a = 1;			//  a  b  全部赋值为 1 
		data[i].b = 1;
		test(data,i);
	}
	for(int i = 0;i<4;i++)
		cout<<data[i].a<<"\t"<<data[i].b<<"\t";//	2       2       2       2       1       1       1       1
	cout<<endl;
	for(int i = 0;i<8;i++)
		cout<<*((int *)(data) + i)<<"\t";	// 		2       2       2       2       1       1       1       1
}
