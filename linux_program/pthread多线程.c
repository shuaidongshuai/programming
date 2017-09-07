#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void *thread1(void *a)
{
	for(int i=0;i<5;i++)
	{
		printf("this is the first thread\n");
		sleep(1);
	}
}
void *thread2(void)
{
	for(int i=0;i<5;i++)
	{
	printf("this is the second thread\n");
	sleep(1);
	}
}
int main()
{
	pthread_t id1,id2;
	pthread_create(&id1,NULL,thread1,NULL);
	pthread_create(&id2,NULL,thread2,NULL);
}