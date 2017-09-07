#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>



void  myhandle(int num)
{
	if (num == SIGINT)
	{
		printf("recv signal SIGINT \n");
	}
	else if (num == SIGUSR1)
	{
		printf("recv signal SIGUSR1 \n");
	}
	else
	{
		printf("recv signal id num : %d \n", num);
	}
}


int main2(void)
{

	pid_t 	pid;
	printf("main ....begin\n");
	
	if (signal(SIGINT, myhandle) == SIG_ERR)
	{
		perror("func signal err\n");
		return 0;
	} 
	if (signal(SIGUSR1, myhandle) == SIG_ERR)
	{
		perror("func signal err\n");
		return 0;
	} 
	
	pid = fork();
	if (pid == -1)
	{
		printf("fork err....\n");
		return 0;
	}
	//子进程向父进程发送信号
	//子进程向同组进程发送信号
	if (pid == 0)
	{
		//pid = getppid();
		//kill(pid, SIGUSR1); //向老爹发信号		收到一条消息
		//kill(0, SIGUSR1); //向进程组发信号		收到两条消息
		
		//向进程组发送信号
		pid = getpgrp();
		killpg(pid, SIGUSR1);//向进程组发信号			收到两条消息
		exit(0);
	}
	
	int n = 3;
	do 
	{
		printf("父进程开始睡眠\n");
		n = sleep(n);
		printf("父进程开始唤醒\n");
	} while (n > 0);
	
	//sleep(n);
	//请思考sleep函数的作用 man sleep
	printf("sleep 函数执行完毕以后返回...\n");
	return 0;

}

int main()
{
	pid_t 	pid;
	printf("main ....begin\n");
	
	if (signal(SIGINT, myhandle) == SIG_ERR)
	{
		perror("func signal err\n");
		return 0;
	} 
	if (signal(SIGUSR1, myhandle) == SIG_ERR)
	{
		perror("func signal err\n");
		return 0;
	} 
	
	pid = fork();
	if (pid == -1)
	{
		printf("fork err....\n");
		return 0;
	}
	
	if (pid == 0)
	{
		//pid = getpgrp();
		pid = getppid();
		//kill(pid, SIGUSR1); //向老爹发信号
		//kill(0, SIGUSR1); //向进程组发信号
		killpg(pid, SIGUSR1);
		exit(0);
	}
	wait(NULL);//必须加上wait  不然，执行几次，会导致终端退出。父进程接收不到消息可能会出错
}

