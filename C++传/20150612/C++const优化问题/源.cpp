#include<iostream>
using namespace std;

void run1(const int *p);//可以改变地址。不能改变内容
void run2(int const *p);//和上面一样
void run3(int *const p);//可以改变内容，不能改变地址
void run4(const int * const p);//不能改变地址，不能改变内容
void run5(int const * const p);//和上面一样



void main()
{
	const int n[5]{1, 2, 3, 4, 5};
	for (int i : n)
	{
		cout << i << endl;
	}
	*((int *)&n) = 100;//改变第一个元素     //const数组没有优化
	for (int i : n)
	{
		cout << i << endl;
	}

	cin.get();
}


void main3()
{
	int i = 10;
	const int a = i;
	//int arr[a];   //这样不行、、C++不会优化。。因为 i 不是常量
	
	//不优化也有好处。我们可以改const的值了

	*((int *)&a) = 300;//因为不优化了。所以是从内存中取出地址。。改地址上的内存，，就能改变const的值
	cout << i << "   " << a << endl;



	cin.get();
}


void main2()
{
	const int a = 10;
	int arr[a];//这样是可以的。。c++优化后。。a就是10          c中不行
}


void main1()
{
	const int a = 10;						//这里我们赋给a的值是常量。。c++编译器会优化。。以后取值都不在内存中取出
	cout << "a 的地址 ：" << &a << endl;

	int *p = (int *)&a;
	cout << "p 指向的地址 ：" << p << endl;

	*((int *)&a) = 1000;

	cout << *(&a) << endl;//a的值并不能改变。。c++编译器优化了。。看见a就在寄存器中取出10   不操作内存
	cout << a << endl;
	cout << p << endl;
	cout << *p << endl;
	/*
	a 的地址 ：    00DDFA90
	p 指向的地址 ：00DDFA90		地址一样
	10
	10
	00DDFA90
	1000					可以看出。。a地址上的内存已经被改变
	*/
	cin.get();
}
