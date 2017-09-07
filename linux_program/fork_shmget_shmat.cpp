#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
int main()
{
	int a,i=10,*pint;
	pid_t pid;
	a=shmget(0,1024,IPC_CREAT|0600);//¿¿¿¿¿¿¿
	pint=(int *)shmat(a,0,0);	//¿pint¿¿¿¿¿¿¿¿¿¿¿¿¿
					//
	*pint=100;			//¿¿¿¿¿¿¿¿¿¿100
	printf("Start of fork tesing\n");
	pid=fork();			//¿¿¿¿0¿
	i++;				//¿¿¿¿¿i¿¿¿¿¿¿¿¿¿¿¿¿¿
	*pint+=1;			//¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
	printf("pid=%d\n",pid);
	printf("i=%d\n",i);
	printf("print=%d\n",*pint);
	shmdt(pint);			//¿¿¿¿¿¿¿¿
	return 0;			//¿¿¿¿¿¿¿¿¿¿¿¿¿pint¿¿   						pint+1  ¿¿+2¿¿¿¿
	
 } 
