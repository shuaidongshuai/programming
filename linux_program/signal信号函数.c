#include<stdio.h>
#include<unistd.h>											// 用来调用  pause
#include<signal.h>											// 用来调用  signal
void func(int sign)
{
	if(sign==SIGINT)
		printf("I have get SIGINT\n");
	else if(sign==SIGQUIT)
		printf("I have get SIGQUIT\n");
}
void main()
{
	printf("waiting for SIGINT OR SIGQUIT\n");
	signal(SIGINT,func);
	signal(SIGQUIT,func);
	pause();												// 等待 信号的到来    
}