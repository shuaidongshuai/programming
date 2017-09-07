// 创建一线程	使用	pthread_cleanup_push	pthread_cleanup_pop	进行保护退出
// pop(0)不执行  	非零 执行
// 从push到pop之间的程序段中的	终止动作（包括调用pthread_exit()和异常终止，不包括return ) 都将执行push所指定的清理函数

//目的：当一个函数发生不可预期的错误时（访问空指针）直接终止函数，，这涉及到资源不能释放的问题
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
// 仔细观察结果	注意  栈是	先进后出
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

void func1()
{
	pthread_cleanup_push((void *)clean,"thread first");	//将函数压入 清除 栈
	pthread_cleanup_push((void *)clean,"thread second");
	
	pthread_t id;
	pthread_create(&id,NULL,thread,NULL);
	pthread_join(id,NULL);
	
	pthread_cleanup_pop(0);									//pthread_cleanup_pop将函数弹出清除栈
	pthread_cleanup_pop(0);														//	0  表示在弹出栈的同时 不执行 该函数
}
void func2()
{
	pthread_cleanup_push((void *)clean,"thread first");
	pthread_cleanup_push((void *)clean,"thread second");
	
	pthread_t id;
	pthread_create(&id,NULL,thread,NULL);
	pthread_join(id,NULL);
	
	pthread_cleanup_pop(1);
	pthread_cleanup_pop(1);														//	1	表示执行
}
int func3()
{
	pthread_cleanup_push((void *)clean,"thread first");
	pthread_cleanup_push((void *)clean,"thread second");
	
	pthread_t id;
	pthread_create(&id,NULL,thread,NULL);
	pthread_join(id,NULL);
	return 0;												// 以return 退出的函数 不执行清除函数		尽管下面是 	1	
	
	pthread_cleanup_pop(1);
	pthread_cleanup_pop(1);
}

int main()
{
	printf("first test\n\n");
	func1();												//会发现func1函数里面的代码没能执行
	printf("\nsecond test\n\n");
	func2();					// 观察先后出现的语句
	printf("\nthird test\n\n");
	func3();
	return 1;
}