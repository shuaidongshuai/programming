#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void *clean(void *a)										//作为线程清理函数
{
	printf("I am cleaning the %s\n",(char *)a);
	return (void *)0;
}

void *thread(void *a)										// 一个调用的线程
{
	printf("I am thread\n");
	return (void *)1;
}
int main()
{
	pthread_cleanup_push((void *)clean,"thread first");	
	pthread_cleanup_push((void *)clean,"thread second");
	
	pthread_t id;
	pthread_create(&id,NULL,thread,NULL);
	pthread_exit((void *)1);									// 线程退出 导致下面语句不执行，exit里面的参数就是 线程 退出返回值的指针
	printf("hello the world\n");
	
	pthread_cleanup_pop(1);
	pthread_cleanup_pop(1);	
}