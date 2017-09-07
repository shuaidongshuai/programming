#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(void)
{
	pid_t pid;
	int sem_id;
	pid=fork();
	if(pid==-1)
	{
		printf("fork error");
		return 1;
	}
	else if(0==pid)
	{
		printf("child process will wait for some second\n");
		sleep(2);															//让子进程等待两秒
		printf("child process PID=%d\n",getpid());
	}
	else 
	{
		wait(NULL);
		printf("parent return child PID=%d\tparent process PID=%d\n",pid,getpid());
	}
	return 0;
	
	
	
	
	
	
	
	
}