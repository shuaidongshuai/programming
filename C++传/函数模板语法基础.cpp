#include <iostream>
#include <typeinfo>
#include<algorithm>
using namespace std;

//一开始老是出错，，原来，，c++里面不能用swap作为函数名，已经被  algorithm 这个头文件给用了，我们可以直接调用 
//template<typename T>
//void swap(T& a,T& b)
//{
//	T c = a;
//	a = b;
//	b = c;
//	cout<<typeid(a).name()<<endl;
//}
int main1()
{
	int a = 1;
	int b = 2;
	swap(a,b);
	char c = 'c',d = 'd';
	swap(c,d);
	cout<<a<<"   "<<b<<endl;
	cout<<c<<"   "<<d<<endl;
}

/*template告诉c++编译器，现在我要进行泛型编程 
  typename 告诉C++编译器 T是一个数据类型，不要报错 
*/

template<typename T>
void mySwap(T& a,T& b)
{
	T c = a;
	a = b;
	b = c;
	cout<<typeid(a).name()<<endl;
}
//void dong(T& a)   //template 只管下一个函数，所以这个函数是错的 
//{}
int main()
{
	int a = 1,b = 2;
	mySwap(a,b);
	cout<<a<<"   "<<b<<endl;
	
cout<<"------------------"<<endl;
	
	//泛型编程函数使用，有两种方法
	 
	 //1.自动类型推导
	char c = 'c',d = 'd';
	mySwap(c,d);
	cout<<c<<"  "<<d<<endl;
	
	//2.具体类型调用
	mySwap<int>(a,b);
	cout<<a<<"   "<<b<<endl;
	
}

