#include<iostream>

using namespace std;

//p pp ppp 都是指针 

int main1()
{
	//* 读成 pointer to
	char a = 'a';
	char* const p = &a;//p是 常量 指向 字符型 
	
	const char* pp = "hello";//pp 指向 字符型 常量 
	//char *pp="dosjgd";
	
	//同上因为C++里面没有const*的运算符，所以const只能属于前面的类型。 char const *   == const char *    const 放在基本数据类型前后没有任何关系 
	char const * ppp = "dong";//ppp 指向  字符型 常量  
	
	cout<<*p<<endl;
	cout<<*pp<<endl;
	cout<<*ppp<<endl;
	
}
int main()
{
	char a = 'a';
	char b = 'b';
	char* const p = &a;//p是 常量 指向 字符型 
	//p = &b;   //错，p的指向不能改变
	*p = 'p';	//对，p指向的值可以改变 
	cout<<*p<<endl;
	
	
	const char* pp = &a;//pp 指向 字符型 常量 
	pp = &b;//对，p的指向可以改变 
	//*pp = 'p';//错，p指向的值不可以改变  
	cout<<*pp<<endl;
	
	
}
