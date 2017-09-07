#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main1()
{
	// signal(SIGCHLD,SIG_IGN);
	pid_t pid;
	int cnt = 0;
	pid=vfork();		
	if(pid<0)
	{
		perror("tile");
		exit(1);
	}
	else if(pid==0)			
	{
		cnt++;
		printf("子进程  cnt = %d\n",cnt);
	}
	else				
	{
		cnt++;
		printf("父进程  cnt = %d\n",cnt);
	}
	
	printf("结束");
	return 0;
	
	//打印结果：
// 子进程  cnt = 1
// 结束父进程  cnt = 266797110
// 结束a.out: cxa_atexit.c:100: __new_exitfn: Assertion `l != NULL' failed.
// 已放弃 (核心已转储)


//vfork 保证子进程先运行，在她调用exec 或exit 之 
// 后父进程才可能被调度运行。如果在调用这两个函数之前子进程依赖于父进程的进一步动 
// 作，则会导致死锁。 
// 这样上面程序中的fork （）改成vfork（）后，vfork （）创建子进程并没有调用exec 或exit，
// 所以最终将导致死锁。
}
int main2()
{
	pid_t pid;
	int cnt = 0;
	pid=vfork();		
	if(pid<0)
	{
		printf("fork error!\n");
		exit(1);
	}
	else if(pid==0)			
	{
		cnt++;
		printf("子进程  cnt = %d\n",cnt);
		exit(0);//加上这句话，是一种方法
	}
	else				
	{
		cnt++;
		printf("父进程  cnt = %d\n",cnt);
	}
	
	printf("结束");
	return 0;
}

int main3()
{
	pid_t pid;
	int cnt = 0;
	pid=vfork();		
	if(pid<0)
	{
		printf("fork error!\n");
		exit(1);
	}
	else if(pid==0)			
	{
		cnt++;
		printf("子进程  cnt = %d\n",cnt);
		//还可以利用int execve(const char *filename, char *const argv[],char *const envp[]);
		char *const argvv[] = {"./test","dong",NULL};//NULL必须加
		execve("./test",argvv,NULL);
		printf("这段话子进程执行不到了，因为跳到test这个程序中去了");
	}
	else				
	{
		cnt++;
		printf("父进程  cnt = %d\n",cnt);
	}
	return 0;
}
int main()
{
	pid_t pid;
	int cnt = 0;
	pid=vfork();		
	if(pid<0)
	{
		printf("fork error!\n");
		exit(1);
	}
	else if(pid==0)
	{
		cnt++;
		printf("子进程  cnt = %d\n",cnt);
		//还可以利用int execve(const char *filename, char *const argv[],char *const envp[]);
		char *const argvv[] = {"ls","-lt",NULL};//NULL必须加
		execve("/bin/ls",argvv,NULL);
		printf("这段话子进程执行不到了，因为跳到 ls 这个程序中去了");
	}
	else
	{
		cnt++;
		printf("父进程  cnt = %d\n",cnt);
	}
	return 0;
}