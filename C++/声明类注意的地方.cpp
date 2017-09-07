#include <iostream>
using namespace std;

class A{
public:
	A()
	{
		cout<<"A类"<<endl;
	}
};

//可以把这个函数放到别的文件中，，更能很好的理解 
A a()				 
{
	cout<<"A函数"<<endl;
}

int main()
{
	A a();//这样不会调用构造函数   、、 编译器认为，这是在声明一个函数。。就算我们没有定义  A a()这样的函数，照样会被认为是声明 
	
	a();//然后我们调用这个函数 
	
	A aa;//调用构造函数 
}
/*
A函数
A类
*/ 
