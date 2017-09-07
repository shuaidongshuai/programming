#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>				// 2 3 调用 shmget 
#include<sys/types.h>			// 3 4 调用 shmat
#include<sys/wait.h>			// 4 5 调用 wait
#include<unistd.h>				// 6 调用 fork  sleep
#include<string.h>				// 7 调用 strncpy  memset
int main(int argc,char **argv)
{
	int shmid;
	if(argc!=2)
	{
		printf("usage %s ....",argv[0]);
		return 1;
	}
	if((shmid=shmget(0,1024,IPC_CREAT))==-1)		// 创建一个共享内存
	{
		printf("creat share memory error");
		return 1;
	}
	//创建子进程
	if(fork())									//在父进程中
	{
		char *p_addr;
		p_addr=shmat(shmid,0,0);				// 把共享内存映射到地址空间上		第二个参数本来是传一个地址，如果填0，表示由系统自动帮你找一个可用的地址
		memset(p_addr,0,1024);					// 初始化地址
		strncpy(p_addr,argv[1],1024);
		wait(NULL);									// 等待子进程结束
	}
	else										//在子进程中
	{
		sleep(1);								// 等待一会  让父进程  成功 copy 一个字符串到  共享内存地址
		char *c_addr;
		c_addr=shmat(shmid,0,0);				//第三个参数  通常为0			这一步  是  获取 共享内存地址
		printf("%s\n",c_addr);
	}
	return 1;
}
