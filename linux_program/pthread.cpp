/*
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);
	第一个参数：保存线程ID
	第二个参数：属性，NULL（默认）
	第三个参数：函数
	第四个参数：参数

RETURN VALUE
       On success, pthread_create() returns 0; on error, it returns an error number, and the contents of *thread are undefined.
						
pthread_t pthread_self(void);
	returns  the  ID  of  the  calling thread

void pthread_exit(void *retval);
	调用线程退出函数，注意和exit函数的区别，任何线程里exit导致进程退出，其他线程未工作结束，主控线程退出时不能return或exit。	
	void *retval:线程退出时传递出的参数，可以是退出值或地址，如是地址时，不能是线程内部申请的局部地址。

int pthread_join(pthread_t thread, void **retval);
	pthread_t thread:回收线程的tid
	void **retval:接收退出线程传递出的返回值
	返回值：成功返回0，失败返回错误号

int pthread_cancel(pthread_t thread);
	在进程内某个线程可以取消另一个线程。

int pthread_detach(pthread_t tid);
	pthread_t tid:分离线程tid
	返回值：成功返回0，失败返回错误号。
	一般情况下，线程终止后，其终止状态一直保留到其它线程调用pthread_join获取
	它的状态为止。但是线程也可以被置为detach状态，这样的线程一旦终止就立刻回收
	它占用的所有资源，而不保留终止状态。不能对一个已经处于detach状态的线程调用
	pthread_join，这样的调用将返回EINVAL。如果已经对一个线程调用了pthread_detach就不
	能再调用pthread_join了。
*/
#include <iostream>
#include <pthread.h>

using namespace std;

void* test1(void *n)
{
	int *num = (int *)n;
	for(int i = 0;i<10;i++)
	{
		(*num)++;
		cout<<"线程1："<<*num<<endl;
	}
	return 0;
}
void* test2(void *n)
{
	int *num = (int *)n;
	for(int i = 0;i<10;i++)
	{
		(*num)++;
		cout<<"线程2："<<*num<<endl;
	}
	return 0;
}
int main()
{
	int num = 0;
	pthread_t pt1;
	pthread_t pt2;
	pthread_create(&pt1,NULL,test1,&num);
	pthread_create(&pt2,NULL,test2,&num);
	pthread_join(pt1,NULL);
	pthread_join(pt2,NULL);
	return 0;
}