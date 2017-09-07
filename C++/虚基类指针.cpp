#include <iostream>
using namespace std;  
//我电脑gcc是64位的版本（没效果啊，不知道啥原因）。。所以请看vs中的代码。。《虚继承——虚函数》 
class A{
	
};
class B1 : virtual public A{			//有一个虚基类     有一个虚基指针，存储虚基类地址 
	
};
class B2 : virtual public A{
	
};
class C1 : virtual public B1{
	
};
class C2 : virtual public B1{
	virtual void b1()
	{
		
	}
};
int main()
{
	cout<<"一个指针大小\t"<<sizeof(int*)<<endl;
	cout<<"A\t"<<sizeof(A)<<endl;
	cout<<"B1\t"<<sizeof(B1)<<endl;
	cout<<"C1\t"<<sizeof(C1)<<endl;
	cout<<"C2\t"<<sizeof(C2)<<endl;
}
