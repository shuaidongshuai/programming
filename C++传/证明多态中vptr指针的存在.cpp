#include <iostream>
using namespace std;

class A{
	public:
		void printf()
		{
			cout<<"hello"<<endl;
		}
};

class B{
	public:
		virtual void printf()
		{
			cout<<"hello"<<endl;
		} 
};

int main()
{
	cout<<sizeof(A)<<endl;
	cout<<sizeof(B)<<endl;//在vs中是4 ，，gcc中是8，，，反正可以证明 在我们定义虚函数时 c++编译器， 在类自动添加了一个东西（vptr指针，指向一个虚函数表 ） 
}
