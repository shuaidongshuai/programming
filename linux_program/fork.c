#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
void main()
{
pid_t pid;
pid=fork();			//创建新进程  fork的特点 调用一次 返回两次
if(pid<0)
{
printf("fork error!\n");
exit(1);
}
else if(pid==0)			//子进程返回0
{
printf("in the child process!\n%d\n",pid);
}
else				//父进程返回子进程ID 多运行几次会发现都不一样
{
printf("in the parent process!\n%d\n",pid);
}
exit(0);
}
