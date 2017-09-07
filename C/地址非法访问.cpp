#include <iostream>
using namespace std;
//在自己的编译器上到还没什么，如果去比赛，如牛客编译器就会报错，地址非法访问 
int main()
{
	int* c = new int;
	
	int* a = c;//加上这句可以骗过编译器，让它不报错，但是我们还是非法访问了未申请的内存地址 
	
	for(int i = 0;i<10;i++)
	{
		a[i] = i;
	}
	
	for(int i = 0;i<10;i++)
	{
		cout<<a[i]<<endl;
	}
}
