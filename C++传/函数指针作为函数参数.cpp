#include <iostream>
using namespace std;

void MyFunc(int a,int b)
{
	cout<<"a = "<<a<<"   b = "<<b<<endl; 
}

//第一种方法 
void MyOp1(void (dong)(int,int))//传递一个函数进去（其实就是传递一个函数首地址进去）
{
	cout<<"--------------"<<endl;
	dong(520,20);
}
//第二种方法 （only add typedef 把void(*)(int,int)这样的函数  取了一个别名而已） 
typedef void(*Func)(int,int);
void MyOp2(Func dong)
{
	cout<<"--------------"<<endl;
	dong(5200,200);
}

//这样做的意义：
void MyFunc2(int a,int b) 
{
	cout<<"hello dong "<<a<<"   "<<b;
}
 
int main()
{
	MyOp1(MyFunc);//MyFunc就是函数首地址  函数名就是一个函数指针 
	MyOp2(MyFunc);
	
	MyOp1(MyFunc2);//意义就在于，只要返回类型是void 参数是 int，int 就可以传进去，然后调用 
} 
