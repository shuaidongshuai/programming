#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
struct msg {
	struct msg *next;
	int num;
};
struct msg *head;
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;//PTHREAD_COND_INITIALIZER来初始化静态定义的条件变量，使其具有缺省属性
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;//POSIX定义了一个宏PTHREAD_MUTEX_INITIALIZER来静态初始化互斥锁

//消费者
void *consumer(void *p)
{
	struct msg *mp;
	for (;;) {
		
		pthread_mutex_lock(&lock);
		while (head == NULL)
			pthread_cond_wait(&has_product, &lock);
		mp = head;
		head = mp->next;
		pthread_mutex_unlock(&lock);
		
		printf("Consume %d\n", mp->num);
		free(mp);
		sleep(rand() % 5);
	}
}
void *producer(void *p)
{
	struct msg *mp;
	for (;;) {
		mp = malloc(sizeof(struct msg));
		mp->num = rand() % 1000 + 1;
		printf("Produce %d\n", mp->num);
		
		pthread_mutex_lock(&lock);
		mp->next = head;
		head = mp;
		pthread_mutex_unlock(&lock);
		
		pthread_cond_signal(&has_product);
		sleep(rand() % 5);
	}
}
int main(int argc, char *argv[])
{
	pthread_t pid, cid;
	srand(time(NULL));
	pthread_create(&pid, NULL, producer, NULL);
	pthread_create(&cid, NULL, consumer, NULL);
	pthread_join(pid, NULL);
	pthread_join(cid, NULL);
	return 0;
}
/*
pthread_cond_wait
//pthread_cond_wait会先解除之前的pthread_mutex_lock锁定的mtx，
        //然后阻塞在等待队列里休眠，直到再次被唤醒
        //（大多数情况下是等待的条件成立而被唤醒，唤醒后，
        //该进程会先锁定先pthread_mutex_lock(&mtx);，
        //再读取资源用这个流程是比较清楚的
*/