#include<iostream>
using namespace std;
int i=10;		//A全局变量   作用域为整个函数
int main()
{
	int i=1;	//B
	{
		int i=5;  //C    变量i的作用域只在{}内
		int j;
		::i=::i+4;	//::是引用A定义的变量，不是B
		j=::i+i;	//这里不加::的i是C定义的变量
		cout<<"::i="<<::i<<",j="<<j<<",i="<<i<<endl;
	}
	cout<<"::i="<<::i<<",i="<<i<<endl;
	return 0;
}
