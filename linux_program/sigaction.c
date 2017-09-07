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

 void handler1(int sig)
 {
	 if(sig == SIGINT)
	 {
		 printf("ctrl+c信号被我修改了\n");
	 }
	 else if(SIGQUIT == sig)
	 {
		 printf("SIGQUIT 信号修改为 退出程序了\n\n");
		 exit(0);
	 }
 }
 void handler2(int num, siginfo_t *info, void * p)
 {
	printf("recv sig :%d\n", num);
	if(num == SIGINT)
	 {
		 printf("ctrl+c信号被我修改了\n");
	 }
	else if(num == SIGQUIT)
	{
		 printf("SIGQUIT 信号修改为 退出程序了\n\n");
		 exit(0);
	}
 }

 // sigaction函数用于改变进程接收到特定信号后的行为。
int main(int argc, char *argv[])
{
		struct sigaction act;
		struct sigaction act2;
		act.sa_handler = handler1;//指定行为
		act2.sa_sigaction = handler2;//也是指定行为
	
	  	sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act2, NULL);

	//On some architectures a union is involved: do not assign to both sa_handler and sa_sigaction
	//在一些联合的架构不被牵涉：sa_handler and sa_sigaction 两个不被同时分配
	//但我上面两个一起分配也没出现问题，但是如果act.sa_handler  之后再 act.sa_sigaction、、这样会报错（估计上面这句话是这个意思）
	
	for (;;)
	{
		sleep(1);
	}
	return 0;
}
