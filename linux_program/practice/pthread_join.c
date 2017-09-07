//	创建一线程，父进程要等待到该线程结束后才能继续执行
#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>			//	3 4	getpid
void *thread(void *a)
{
	printf("this is the thread	%u\n",(unsigned int)pthread_self());
	return NULL;
}
int main()
{
	pthread_t id;
	pthread_create(&id,NULL,thread,NULL);
	pthread_join(id,NULL);
	printf("this is main gid %d",getpid());
	return 1;
}