#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
int a=1;
int b=10;									// 全局变量
void *create(void *arg)
{
	printf("a2=%d\n",a);					// 规定	使用	数据段里面数据		不使用栈里面的数据
	printf("b2=%d\n",b);
	a++;
	b++;
}
int main()
{
	int a=5;								// 局部变量		栈里面的数据
	printf("a1=%d\n",a);
	printf("b1=%d\n",b);
	pthread_t id;
	pthread_create(&id,NULL,create,NULL);
	sleep(1);
	
	printf("a3=%d\n",a);
	printf("b3=%d\n",b);
	return 1;
}