#include<sys/sem.h>
#include<stdio.h>
int main()
{
	int semid;

    semid=semget(0,1,IPC_CREAT|0666);//创建了一个权限为 666  的信号量

    printf("semid=%d\n",semid);
												//我们可以用ipcs –s  来查看是否创建成功。
												//用ipcrm  -s   semid号来删除指定的信号量。
	return 0;
}