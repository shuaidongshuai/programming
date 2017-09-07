//当子进程先死这种情况  叫做   僵尸进程
//当父进程先死		--	--	--	--孤儿进程
#include <stdio.h>
#include <signal.h>

#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	signal(SIGCHLD, SIG_IGN);//增加一个信号，通知内核  父进程不会去处理子进程结束信号。内核自己处理
	printf("befor fork pid:%d \n", getpid());

	pid = fork();
	if (pid == -1)	
	{
		perror("tile");
		return -1;
	}
	if (pid > 0)
	{
		printf("parent: 子进程号:%d \n", getpid());
		sleep(9);//让子进程先结束
	}
	else if (pid == 0)
	{
		printf("child: %d, parent: %d \n", getpid(), getppid());
		//sleep(100);
	}

	return 0;
}
