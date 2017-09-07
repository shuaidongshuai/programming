// 启动A进程 	创建一共享内存，并向其写入一些数据
// 启动B进程 从A创建的内存中读出数据
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#include<unistd.h>

#include<string.h>
#include<sys/wait.h>
int main(int argc,char** argv)
{
	int shmid;
	shmid=shmget(0,1024,IPC_CREAT);		//创建				//必须在fork 之前创建     不然子进程不能继承父进程的  共享内存
	if(fork())
	{
	char *buf;
	buf=shmat(shmid,0,0);				//映射
	strcpy(buf,"hello dong");
	printf("%s\n",buf);
	wait(NULL);
	}
	else
	{
		sleep(1);
		char *buff;
		buff=shmat(shmid,0,0);
		printf("%s\n",buff);
	}
	return 1;
}