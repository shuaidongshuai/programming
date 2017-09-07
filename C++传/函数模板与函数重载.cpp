#include <iostream>
using namespace std;
/*重载函数模板
匹配约定：
	1.找到和使用最符合函数名和函数参数类型的函数						精确函数 
	2.否则，找到一个函数模板，将其实例化产生一个匹配的模板函数			模板函数 
	3.否则，找到通过类型转换进行参数匹配的重载函数 						重载函数 
	4.如果都没有找到，那么调用错误，或者二义性 
*/ 
void print1(int a,int b)
{
	cout<<"++++++++++++普通函数"<<endl;
	cout<<a<<"  "<<b<<endl;
}
template<class T>
void print1(T a,T b)
{
	cout<<"++++++++++++模板函数"<<endl;
	cout<<a<<"  "<<b<<endl;
}
template<class T>
void print2(T a,T b)		//a b 类型必须一致 
{
	cout<<"---------------函数模板"<<endl;
	cout<<a<<"  "<<b<<endl;
}

void print2(int a,char b)	//解决类型必须一致的方法1  函数重载，，重载一个函数模板 
{
	cout<<"---------------普通函数"<<endl;
	cout<<a<<"  "<<b<<endl;	
}

int main()
{
	int a = 49;
	char b = 'A';
	print1(a,b);//49  65
	//printf2(a,b);				这就是区别1   普通函数可以进行隐式类型转换，而函数模板不能 
	print2(a,b);//49  A 精确匹配函数 
	
	print2(a,a);//49  49 匹配的是函数模板 
	
	print2(b,a);//65  1 匹配的是类型转换后的重载函数 	
	
	print1(1000,2000);//匹配的是精确函数
	//如果我们非要用模板函数加一个<>就行了 
	print1<>(1000,2000);//匹配的是模板函数 
} 
