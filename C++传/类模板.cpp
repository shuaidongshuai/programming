#include <iostream>
using namespace std; 

template<class T>//下面可以 不用T 模板，，，，但是不能调用该类，，好像只要不调用类，编译器是不会去检查类中的内容的 
class A{
	public:
		A(T a){
			this->a = a;
		}
		T a; 
};

class B:public A<int>{		//继承的时候也必须加上“模板形参”
	public:
		B(int a,int b):A(a){ //在继承的时候加上了 “模板形参” 这里就可以不加了 
			this->b = b;
		}
		int b;
}; 

void showA(A<int> a)//当做参数传进去的时候也必须加上“模板形参”
{
	cout<<a.a<<endl;
}

int main1()
{
	//cout<<sizeof(A)<<endl; 这样也会让编译器去检查类中的成员 
	A<int> a(1); //创建对象的时候  必须加上“模板形参”  不然编译器不知道该类有多大
	
	showA(a);
}

int main()
{
	B b(4123,2);
	showA(b);
} 
