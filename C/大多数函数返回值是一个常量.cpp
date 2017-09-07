#include<iostream>
using namespace std;

void test(char &c)//这里最好不这样写 
{
	cout<<"参数是&c  "<<c<<endl;
}

//最好这样写,,通用，，只是不能改c的值 
void test2(const char &c)
{
	cout<<"参数是const char &c  "<<c<<endl;
}

char get()//注意这里不是返回的 变量c    而是返回的常量 'a'   因为栈马上就毁了，返回变量没意义 
{
	char c = 'a';
	return c;
}
char &get(int i)
{
	char b = 'B';
	char & c = b; 
	return c;
} 
int  main1()
{
	//test(get());    //这句话是不能通过编译的。。。因为  test  不接受字符常量 
	test2(get()); 
	
	
	//test test2 都能通过编译。。 
	char c = 'A';
	test(c);		//这里可以看成传进去一个 'A'  字符常量 
	test2(c);
	
	test(get(1));//除非本分返回值是一个引用，否侧不能通过编译
}








int &pget()//注意，除非传进来的值有引用，，返回也返回那个引用，不然最好别返回引用 
{
	int i =10;
	return i;
}
int main()
{
	int i = pget();
	cout<<i<<endl; 
	cout<<i<<endl; //这样没问题，因为这里是赋值，是吧 i 赋值为了 10，，引用没有传播出去 
	
	int &ii = pget();//因为 ii 也是一个引用。引用的还是栈上的变量，，所以出问题了 
	cout<<ii<<endl;  
	cout<<ii<<endl; //出错了，，因为栈的内存被回收了 
}
