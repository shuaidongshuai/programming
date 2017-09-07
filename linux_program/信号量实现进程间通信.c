#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdio.h>
#include<unistd.h>
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
int main()
{
	key_t key;
	int semid;
	union semun arg;
	struct sembuf sb={0,-1,IPC_NOWAIT};
	if((key=ftok("/home/dong/dd",'c'))==-1)		//创建新进程		用这个函数的原因就是  指定一个ID  放在key 中
	{
		perror("ftok error\n");
		return 1;
	}
	if((semid= semget(key,1,IPC_CREAT|0660) )==-1)
	{
		perror("semget error");
		return 1;
	}
	arg.val=5;											//设置单个信号量的值
	printf("可用资源共有%d个\n",arg.val);
	int a=semctl(semid,0,SETVAL,arg);
	if(a==-1)
	{
		perror("semctl error");
		return 1;
	}
	printf("semctl返回值为0则调用成功=%d\n",a);
	while(1)
	{
		if(semop(semid,&sb,1)==-1)
	{
		perror("semop error");
		return 1;
	}
		sleep(2);
	}
	semctl(semid,0,IPC_RMID,arg);			//IPC_RMID  是删除的意思           从  内核中删除信号量集合
	return 0;
}