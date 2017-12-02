#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h> 
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
/*
结果：进程要实现互斥
1.要给锁设置属性：PTHREAD_PROCESS_SHARED 线程进程共享
2.互斥的变量必须是同一个，也就是说要对共享区的变量进行互斥，因为copy-on-write机制
*/
typedef struct Dong{
	int a;
	int *b;
}Dong;

pthread_mutex_t mutex;

void func(Dong *i){
	for(int j = 0; j < 20; ++j){
		pthread_mutex_lock(&mutex);
		++i->a;
		++*i->b;
		printf("%d  %d\n", i->a, *i->b);
		pthread_mutex_unlock(&mutex);
	}
}
int main(void)
{
	pthread_mutexattr_t mutex_shared_attr;
	pthread_mutexattr_init(&mutex_shared_attr);//初始化互斥对象属性     
	pthread_mutexattr_setpshared(&mutex_shared_attr,PTHREAD_PROCESS_SHARED);//设置互斥对象为PTHREAD_PROCESS_SHARED共享，即可以在多个进程的线程访问,PTHREAD_PROCESS_PRIVATE为同一进程的线程共享 
	
	if( pthread_mutex_init(&mutex, &mutex_shared_attr) != 0 )	{
		printf("error pthread_mutex_init\n");
		return 0;
	}
	Dong *i = (Dong *)mmap(NULL,sizeof(Dong),PROT_READ|PROT_WRITE,  
           MAP_SHARED|MAP_ANONYMOUS,-1,0); 
	i->b = (int *)malloc(sizeof(int));
	
	pid_t pid;
	pid=fork();
	if(pid==-1) {
		printf("fork error");
		return 1;
	}
	else if(0==pid){
		func(i);
	}
	else{
		func(i);
	}
	pthread_mutex_destroy( &mutex );
	return 0;
}