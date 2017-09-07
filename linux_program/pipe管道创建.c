#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#define MAX 100
int main()
{
	int fd[2],pid,line;
	char message[MAX];
	//创建管道
	if(pipe(fd)==-1)									// pipe() 创建失败返回-1
	{
		perror("create pipe failed!");
		return 1;
	}
	//创建新进程
	else if((pid=fork())<0)
	{
		perror("not create a new process ");
		return 1;
	}
	//子进程
	else if(0==pid)
	{
		close(fd[0]);									//关闭子进程的 读
		printf("child process send message \n");
		write(fd[1],"Welcome to mrsoft!",19);
	}
	else
	{
		pid_t pid=wait(NULL);							//等待子进程结束	
		printf("child ID:%d\n",pid);
		close(fd[1]);									//关闭父进程的 写
		printf("parent process receive message is :\n");
		line=read(fd[0],message,MAX);					//读取消息返回消息长度
		write(STDOUT_FILENO,message,line);				//将消息写入到终端
		printf("\n");
		exit(0);
	}
}