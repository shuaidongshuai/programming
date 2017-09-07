#include <iostream>
using namespace std;

void test(char &c)//这里最好不这样写 
{
	cout << "参数是&  " << c << endl;
}

//最好这样写,,通用，，
void test2(const char &c)
{
	cout << "参数是const char &  " << c << endl;
}

char get()//注意这里不是返回的 变量c    而是返回的常量 'a'   因为栈马上就毁了，返回变量没意义 
{
	char c = 'a';
	return c;
}
char &get(char &c)
{
	//char b = 'B';
	char & cc = c;
	return cc;
}
int  main()
{
	//test(get());    //这句话是不能通过编译的。。。因为  test  不接受字符常量 
	test2(get());


	//test test2 都能通过编译。。 
	char c = 'A';
	test(c);		//这里可以看成传进去一个 'A'  字符常量 
	test2(c);

	test(get(c));//除非返回值是一个引用，否侧不能通过编译,,,而且最好返回的不是函数内部的引用，可能被销毁，GCC和Vs不一样
	test2(get(c));//除非返回值是一个引用，否侧不能通过编译

	cin.get();
	return 0;
}