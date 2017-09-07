#include<stdio.h>
#include<stack>
using namespace std;
//这是属于c++的范畴 
int main()
{
	stack<char>cstack;
	char c;
	int n=6;
	while(--n)// 这里 --n 和 n-- 的区别就在于  --n先减一在判断n是否为0   n-- 先判断是否为0  再执行 --  
	{
		c = getchar();
		getchar();
		cstack.push(c);//入队列 
	}
	//判断对列是否为空 函数为:empty()	不为空返回 0 
	while(!cstack.empty())
	{
		printf("top = %c\n",cstack.top());
		printf("size = %d\n\n",cstack.size());
		cstack.pop();//出队列
	}
}
