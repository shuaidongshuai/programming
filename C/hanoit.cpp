#include<stdio.h>
#include<time.h>
void move(char x,char y)
{
	printf("%c->%c\t",x,y);
}
void hanoit(int n,int a,int b,int c)
{
	if(n==1) move(a,c);			//始终是a移到c 
	else
	{
		hanoit(n-1,a,c,b);		//将a上的盘子借助c移到b上 if最后是将倒数第二个盘移动到b上     （1） 
			move(a,c);			//始终是a->c 
		hanoit(n-1,b,a,c);		//将 b 上的盘子借助 a 移到 c 上                                     （2）  1和2的步骤是一样多的 
	}
}
int main()
{
	int n=3;
	hanoit(n,'a','b','c');		//总之  还是没理解。。。。哈哈 
}
