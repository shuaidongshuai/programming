
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>


//演示信号从产生到抵达的整个过程
//信号的阻塞和解除阻塞综合实验

#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

void handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("recv a sig=%d\n", sig);
		printf("\n\n\n");
		//fflush(stdout);
	}
	else if (sig == SIGQUIT)//ctr + \ 用来结束  SIGINT 信号
	{
		sigset_t uset;
		sigemptyset(&uset);						//信号位清空
		sigaddset(&uset, SIGINT);				//给SIGINT信号位置1
		
		sigprocmask(SIG_UNBLOCK, &uset, NULL);	//解除阻塞
		//signal(SIGINT, SIG_DFL) ;
	}
}

void printsigset(sigset_t *set)
{
	int i;
	for (i=1; i<NSIG; ++i)
	{
		if (sigismember(set, i))
			putchar('1');
		else
			putchar('0');
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	sigset_t pset; //用来打印的信号集
	sigset_t bset; //用来设置阻塞的信号集
	
	sigemptyset(&bset);
	sigaddset(&bset, SIGINT);//SIGINT==2  信号位被设置为1
	
	if (signal(SIGINT, handler) == SIG_ERR)//这里我们更改了ctrl+c的信号处理功能，所以到时候程序并不能退出
		ERR_EXIT("signal error");		//每当我们按下ctrl+c时就会打印recv a sig=2
		
	if (signal(SIGQUIT, handler ) == SIG_ERR)
		ERR_EXIT("signal error");

	//ctrl+c信号被设置成阻塞，即使用户按下ctl+c键盘，也不会抵达
	sigprocmask(SIG_BLOCK, &bset, NULL);
	
	//不要被下面这个信号位给迷惑了，没有下面这个循环，照样实验能很好的验证，只是我们看不到信号位的变化罢了
	for (;;)
	{
		sigpending(&pset);//获取未决 字信息
		printsigset(&pset);//打印信号未决  sigset_t字
		sleep(1);
	}
	return 0;
}
//阻塞之后，我们按下ctrl+c之后没有立马出来recv a sig=2，而是当我们按下ctrl+\ 才出来，
//因为handler中我们解除了SIGINT的阻塞


