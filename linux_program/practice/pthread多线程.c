//	创建以线程，并向该线程处理函数传递一结构
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
struct dong
{
	int a;
	char *b;
};
void *thread(void *arg)
{
	struct dong *c=(struct dong *)arg;
	printf("a=%d\n",c->a);
	printf("b=%s\n",c->b);
	printf("this is the pthread\n");
}
int main()
{
	struct dong *str;
	str=(struct dong*)malloc(sizeof(struct dong));			//  这一步不能少，少了这一步 搞的我半天不知道原因
	str->a=100;
	str->b="hello dong";
	pthread_t id;
	pthread_create(&id,NULL,thread,(void *)str);			// 注意接头体里面的参数是固定的	记得强制类型转化
	sleep(1);
	return 0;
}