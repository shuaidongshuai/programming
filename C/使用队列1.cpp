#include<stdio.h>
#include<queue>
using namespace std;
//这是属于c++的范畴 
int main()
{
	queue<char>cque;
	char c;
	int n=6;
	while(--n)// 这里 --n 和 n-- 的区别就在于  --n先减一在判断n是否为0   n-- 先判断是否为0  再执行 --  
	{
		c = getchar();
		getchar();
		cque.push(c);//入队列 
	}
	//判断对列是否为空 函数为:empty()
	while(!cque.empty())
	{
		printf("front = %c\n",cque.front());
		printf("back = %c\n",cque.back());
		printf("size = %d\n\n",cque.size());
		cque.pop();//出队列
	}
}
