/* 每隔一秒发出一个SIGALRM，每隔0.5秒发出一个SIGVTALRM信号：*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
int sec;
void sigroutine(int signo)
{
	switch (signo)
	{
		case SIGALRM:
		printf("Catch a signal -- SIGALRM \n");
		signal(SIGALRM, sigroutine);
		break;
		case SIGVTALRM:
		printf("Catch a signal -- SIGVTALRM \n");
		signal(SIGVTALRM, sigroutine);
		break;
	}
	fflush(stdout);
	return;
}
int main()
{
	struct itimerval value, ovalue, value2; //(1)
	sec = 5;
	printf("process id is %d\n", getpid());
	signal(SIGALRM, sigroutine);
	signal(SIGVTALRM, sigroutine);
	value.it_value.tv_sec = 1;
	value.it_value.tv_usec = 0;
	value.it_interval.tv_sec = 1;
	value.it_interval.tv_usec = 0;
	setitimer(ITIMER_REAL, &value, &ovalue); //(2)			ITIMER_REAL: 以系统真实的时间来计算，它送出SIGALRM信号。
	value2.it_value.tv_sec = 0;
	value2.it_value.tv_usec = 500000;
	value2.it_interval.tv_sec = 0;
	value2.it_interval.tv_usec = 500000;
	setitimer(ITIMER_VIRTUAL, &value2, &ovalue);		//	ITIMER_VIRTUAL: 以该进程在用户态下花费的时间来计算，它送出SIGVTALRM信号。
	for(;;)
	;
}
/*
it_interval指定间隔时间，it_value指定初始定时时间。如果只指定it_value，就是实现一次定时；
如果同时指定 it_interval，则超时后，系统会重新初始化it_value为it_interval，实现重复定时；两者都清零，则会清除定时器。
tv_sec提供秒级精度，tv_usec提供微秒级精度，以值大的为先，注意1s = 1000000us。
ovalue用来保存先前的值，常设为NULL。
如果是以setitimer提供的定时器来休眠，只需阻塞等待定时器信号就可以了。
*/