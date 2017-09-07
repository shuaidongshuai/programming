#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
int main()
{
	int a;
	pid_t pid,pgid;
	pid=getpid();//获取进程ID
	pgid=getpgrp();//获取进程组ID
	a=setpgid(pid,pgid);//如果组ID和进程ID相同，创建一个新的进程组。如果不同那么将pid 加入到pgid 进程中
	printf("a=%d\npid=%d\npgid=%d\n",a,pid,pgid);
	return 0;
}



 
