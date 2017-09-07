#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
pthread_t tid[10];
void thread_handler(void *arg)
{
	printf("tid%d:%u,pid:%u\n",(int)arg, (unsigned)pthread_self(),(unsigned)getpid());
	while(1)
		sleep(2);
}

int main()
{
	int i, ret;
	pid_t pid;
	printf("main tid:%u,pid:%u\n",(unsigned)pthread_self(),(unsigned)getpid());
	for(int i = 0; i < 10; i++)
	{
		if((ret = pthread_create(&tid[i],NULL,thread_handler,NULL)) !=0)
		{
			fprintf(stderr, "pthread_create:%s\n",strerror(ret));
			return 0;
		}
	}
	sleep(3);
	pid = fork();
	if(pid == 0)
	{
		printf("son tid:%u,pid:%u\n",(unsigned)pthread_self(),(unsigned)getpid());
		while(1)
			sleep(1);
	}
	while(1)
		sleep(3);
	return 0;
}
/*
tid0:3077880688,pid:2418
tid1:3069487984,pid:2418
tid2:3061095280,pid:2418
tid3:3052702576,pid:2418
tid4:3044309872,pid:2418
tid5:3035917168,pid:2418
tid6:3027524464,pid:2418
tid7:3019131760,pid:2418
tid8:3010739056,pid:2418
tid9:3002346352,pid:2418
son tid:3077888816,pid:2429
从结果可以看出，测试程序中所有线程的PID都相同

在另一个终端调用pstree -pu
─gnome-terminal(1624,zx)─┬─bash(1628)
│                         ├─bash(1704)───pstree(2430)
│                         ├─bash(1927)───test(2418)─┬─test(2429)
│                         │                         ├─{test}(2419)
│                         │                         ├─{test}(2420)
│                         │                         ├─{test}(2421)
│                         │                         ├─{test}(2422)
│                         │                         ├─{test}(2423)
│                         │                         ├─{test}(2424)
│                         │                         ├─{test}(2425)
│                         │                         ├─{test}(2426)
│                         │                         ├─{test}(2427)
│                         │                         └─{test}(2428)
从中可以看出，每个线程的PID其实是不同的，因为测试程序是理想状态，只有一个主线程在创建线程，所以PID的值都是连续的。

*/