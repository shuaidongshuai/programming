// 在父进程中创建一个无名管道，并创建子进程来读取该管道，父进程来写
#include<unistd.h>		// 1 调用 pipe fork  write close  sleep
#include<stdio.h>
int main()
{
	int fd[2];
	if(pipe(fd)==-1)							// 创建无名管道  成功，返回0，否则返回-1。
	{
		printf("creat pipe error\n");
		return 1;
	}
	int nread;
	int pid=fork();
	printf("%d\n",pid);
	if(pid>0)//父进程
	{
		close(fd[0]);
		write(fd[1],"hello child",11);
		sleep(2);
	}
	else if(pid==0)//子进程
	{
		sleep(1);
		close(fd[1]);
		char buf[100];						// buffer 缓冲区			好像规定必须是数组，，刚开始弄成 指针  读不出来  半天没找出错误
		nread=read(fd[0],buf,100);
		for(int i=0;i<nread;i++)
		printf("%c",buf[i]);
		printf("\n");
	}
	else
	{
		printf("fork error");
	}
	return 1;
}