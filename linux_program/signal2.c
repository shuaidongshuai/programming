#include <sys/types.h>
#include <unistd.h>


#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

/*
       #include <signal.h>

       typedef void (*sighandler_t)(int);

       sighandler_t signal(int signum, sighandler_t handler);
*/

void handler(int num)
{
	printf("recv num:%d \n", num);	
	if (num == SIGQUIT)
	{
		//exit(0);
	}
}
//信号异步通知事件 。。。。。（我的应用程序dm01）可以随时被信号机制中断。。。
//如果我我写了信号处理函数handler
//那么当信号发生时，会自动调用我写的函数。。。。
void main2()
{
	//注册一个信号
	//SIGINT  是ctrl+c 会产生2号信号。。。 中断应用程序
	signal(SIGINT, handler);
	
	//signal(SIGQUIT, handler);//SIGQUIT也是等待来自键盘的一个信号
	
	while(getchar() != 'a')
	{
		
	}
	
	printf("main...Begin\n");
}
int main()
{
	//注册一个信号
	//SIGINT  是ctrl+c 会产生2号信号。。。 中断应用程序
	signal(SIGINT, handler);
	printf("如果你键入a字符，那么将恢复 SIGINT 的行为\n");
	while(getchar() != 'a')
	{
		
	}
	
	//让这个信号恢复默认行为 SIG_DFL
	signal(SIGINT, SIG_DFL);
	printf("信号恢复默认行\n");
	while(1)
	{
		
	}
	
	printf("main...end\n");
}
 // signal()  returns  the previous value of the signal handler, or SIG_ERR
 // on error.  In the event of an error,  errno  is  set  to  indicate  the cause  //indicate 表明
//测试函数返回值
void main23()
{
	char tmpchar;
	//注册一个信号
	//SIGINT  是ctrl+c 会产生2号信号。。。 中断应用程序
	__sighandler_t old = signal(SIGINT, handler);
	if (SIG_ERR == old)
	{
		perror("signal err"); //errno
	}
	while( (tmpchar = getchar()) != 'a' )
	{
	}
	
	printf("main...end\n");
		
	/*
	char tmpchar;
	//注册一个信号
	//SIGINT  是ctrl+c 会产生2号信号。。。 中断应用程序
 	if (signal(SIGINT, handler) == SIG_ERR)
 	{
 			perror("signal err"); //errno
 			exit(0);
 	} 
	while(1)
	{
		pause();
	}
	printf("main...end\n");*/
}
