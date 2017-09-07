#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>
int main()
{
	int shmid,size;
	pid_t pid;
	char *addr;
	shmid=shmget(0,1024,IPC_CREAT|0660);		//shmget 创建共享内存		ipc_creat 创建  | 后面的是权限
	if(shmid==-1)
	{
		perror("create share memory failed");
		return 1;
	}
	addr=(char *)shmat(shmid,0,0);					//将共享内存  附加到指定进程的地址空间中   但后两个参数都为0  所以是自动选择一个合适的内存地址
	if(addr==(char *)(-1))
	{
		perror("cannot attach ");
		return 1;
	}
	printf("share menmory segment's address: %x\n",(int)addr);
	strcpy(addr,"welcome to mrsoft!");					//为共享内存 的指定地址  赋值（增加内容） 
	pid=fork();					//创建新进程
	if(-1==pid)
	{
		perror("error");
		return 1;
	}
	else if(pid==0)
	{
		printf("child process string is '%s'\n",addr);//子进程获得获得共享内存里面的东西
	}
	else
	{
		wait(NULL);
		printf("parent process string is '%s'\n",addr);	//父进程  也可以获得 共享内存里面的东西
		if(shmdt(addr)==-1)					//使附加 内存 从 进程 中分离出来
		{
			perror("release failed");
			return 1;
		}
		if(shmctl(shmid,IPC_RMID,NULL)==-1)		//IPC_RMID  删除shmid 标识符 所指的 共享内存区域
		{
			perror("failed");
			return 1;
		}
	}
	return 0;
}