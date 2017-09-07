#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handler(int num)
{
	printf("\n recv num:%d \n", num);	
	if (num == SIGQUIT)
	{
		//exit(0);
	}
}

int main1()
{
	pid_t pid;
	signal(SIGINT,handler);
	
	printf("开始睡眠\n");
	sleep(100);//100s		//sleep 属于可中断睡眠，当ctrl+c 之后那么这个函数就不顶用了，直接执行下面语句
	printf("睡眠结束\n");
}
// RETURN VALUE
// Zero if the requested time has elapsed, 	//如果时间到了返回 0 
//or the number of seconds left to sleep, if the call was interrupted by a signal handler.//如果时间没有到，被打断，返回剩余时间
int main()
{
	int n;
	pid_t pid;
	signal(SIGINT,handler);
	
	printf("开始睡眠\n");
	//如果我们非要函数睡眠10s才能醒，那么可以这样做
	do
	{
		n = sleep(10);//在此期间再怎么按ctrl+c  都不会执行到printf
	}while(0 != n);
	printf("睡眠结束\n");	
}