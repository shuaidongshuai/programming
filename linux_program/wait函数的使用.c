#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
void exit_s(int status)							//用于判断子进程是否正常退出
{
	if(WIFEXITED(status))						//WIFEXITED(status)当子进程正常退出时返回真值
		printf("\tnormal exit   status=%d\n\n",WEXITSTATUS(status));//WEXITSTATUS  返回子进程正常退出时的状态
	else if(WIFSIGNALED(status))				//WIFEXITED(status) 作用和 WIFEXITED() 相反
		printf("signal exit!    status=%d\n\n",WTERMSIG(status));
}
int main2()
{
	pid_t pid,a;
	int status;
	if((pid=fork())<0)							//创建一个子进程
	{
		printf("child process errot!\n");
		exit(0);
	}
	else if(0==pid)								//判断是否是子进程
	{
		printf("this is a child process\n");
		exit(110);
	}									//从这一下  都是父进程里面的内容了
	if(wait(&status)!=pid)				/*  父进程一旦调用了 wait 就立即阻塞自己，
										由wait自动分析是否当前进程的某个子进程已经退出
										，如果让它找到了这样一个已经变成僵尸的子进程，
										wait就会收集这个子进程的信息，并把它彻底销毁后返回；
										如果没有找到这样一个子进程，wait就会一直阻塞在这里，直到有一个出现为止*/
	{
		printf("this is a parent process \n wait error");
		exit(0);
	}
	exit_s(status);
}

int main3()
{
	//接下来看一下  结束子进程  后的效果
	pid_t pid;
	pid_t pid1;
	int status;
	printf("主进程  PID :　%d\n",getpid());
	if((pid=fork())<0)							//创建一个子进程
	{
		printf("child process errot!\n");
		exit(0);
	}
	else if(0==pid)								//判断是否是子进程
	{
		printf("this is a child process  PID : %d \n",getpid());
		//  exit(20);			在这我们不用正常退出
		pid1=getpid();
		kill(pid1,9);		//这是结束进程
	}
	if(wait(&status)!=pid)
	{
		printf("this process PID : %d \t wait error\n",getpid());//父进程不会进入
		exit(10);
	}
	exit_s(status);
}

int main4()
{
	pid_t pid;
	pid_t pid2;
	int status;
	printf("主进程  PID :　%d\n",getpid());
	if((pid=fork())<0)							//创建一个子进程
	{
		printf("child process errot!\n");
		exit(0);
	}
	else if(0==pid)				
	{
		printf("this is a child process  PID : %d \n",getpid());
		
		pid2=getpid();
		kill(pid2,17);		//这是进入父进程
	}					
	if(wait(&status)!=pid)
	{
		printf("this process PID : %d \t wait error\n",getpid());//子进程会进入到这里	
		exit(11);
	}
	exit_s(status);
}
void main()
{
	pid_t pid = 0;
	int status;
	pid_t pid3;
	if((pid=fork())<0)							//创建一个子进程
	{
		printf("child process errot!\n");
		exit(0);
	}
	else if(0==pid)		
	{
		printf("this is a child process\n");
	
		pid3=getpid();
		kill(pid3,18);		//这是终止进程
	}
	if(wait(&status)!=pid)		
	{
		printf("this is a  process \t wait error\n");
		exit(12);
	}
	exit_s(status);
	exit(0);
}
// wait():  on  success, returns the process ID of the terminated child; on error, -1 is returned.
// 结束( terminate的过去式和过去分词 ) 		返回的是子进程的ID

