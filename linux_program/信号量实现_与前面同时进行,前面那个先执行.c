#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
/*union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};*/									//由于前面那个文件写了  union semn 共用体    所以这个文件可以不用写			
int main(void)
{
	key_t key;
	int semid,semval;
	// union semun arg;
	if((key=ftok("/home/dong/dd",'c'))==-1)					
	{
		perror("key error\n");
		return 1;
	}
	if((semid=semget(key,1,IPC_CREAT|0666))==-1)			// 一般设置为1   还没搞清楚
	{
		perror("semget error");
		return 1;
	}
	while(1)
	{
		if((semval=semctl(semid,0,GETVAL,0))==-1)			//读取单个信号量的值
		{
			perror("semctl error");
			return 1;
		}
		if(semval>0)
		{
			printf("还有 %d 个资源可以使用\n",semval);
		}
		else
		{
			printf("没有资源可以用%d\n",semval);
			break;
		}
		sleep(2);
	}
	exit(0);
	
}