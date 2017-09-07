#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void *create(void *arg)
{
	int *num;
	num=(int *)arg;
	printf("creat the paramters is %d\n",*num);
}
int main()
{
	pthread_t id;
	int a=4;
	int *arc=&a;
	pthread_create(&id,NULL,create,(void *)arc);
	//sleep(1);
	return 1;
}