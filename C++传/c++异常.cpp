#include <iostream>
using namespace std;

//引入异常的意义：1.容易找出错误
				//2.让程序不因为一些可见的异常而崩溃，，如果我们有相应的措施，就不妨碍程序的继续运行 

int div(int a,int b)
{
	try{
		if(b == 0)
		{
			throw 1;
		}
		if(a == 0)
		{
			throw 2;
		}
		return a/b;
	} catch(int code){
		if(code == 1)
		{
			cout<<"被除数不能为0"<<endl;
		}
		if(code == 2)
		{
			cout<<"除数不能为0"<<endl;
		}
		return 0;
	}
}

int main()
{
	div(0,0);
	cout<<"-------------"<<endl;
	div(0,1);
}
