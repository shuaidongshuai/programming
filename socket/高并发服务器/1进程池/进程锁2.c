#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/wait.h>

struct mt {
int num;
pthread_mutex_t mutex;
pthread_mutexattr_t mutexattr;
};
struct mt * mm;

void test(struct mt * mm)
{
	for (int i=0;i<10;i++){
		printf("PID：%d \n",getpid());
		pthread_mutex_lock(&mm->mutex);
		mm->num += 1;
		printf("PID：%d  num = :%d\n",getpid(),mm->num);
		//sleep(3);
		pthread_mutex_unlock(&mm->mutex);
	}
}
void test2()
{
	for (int i=0;i<10;i++){
		printf("PID：%d \n",getpid());
		pthread_mutex_lock(&mm->mutex);
		mm->num += 1;
		printf("PID：%d  num = :%d\n",getpid(),mm->num);
		//sleep(3);
		pthread_mutex_unlock(&mm->mutex);
	}
}
int main(void)
{
	int fd, i;
	pid_t pid;
	
	unlink("mt_test");//删除文件
	fd = open("mt_test", O_CREAT | O_RDWR, 0777);
	/* 不需要write,文件里初始值为0 */
	ftruncate(fd, sizeof(*mm));//ftruncate会将参数fd指定的文件大小改为参数length指定的大小。
	mm = mmap(NULL, sizeof(*mm), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);
	memset(mm, 0, sizeof(*mm));
	/* 初始化互斥对象属性*/
	pthread_mutexattr_init(&mm->mutexattr);
	/* 设置互斥对象为PTHREAD_PROCESS_SHARED共享，即可以在多个进程的线程访问,PTHREAD_PROCESS_PRIVATE为同一进程的线程共享*/
	pthread_mutexattr_setpshared(&mm->mutexattr,PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(&mm->mutex, &mm->mutexattr);
	pid = fork();
	if (pid == 0){
		//test(mm);
		test2();
	}
	else if (pid > 0) {
		// test(mm);	//可以传值
		test2();
		wait(NULL);
	}
	pthread_mutex_destroy(&mm->mutex);
	pthread_mutexattr_destroy(&mm->mutexattr);
	/* 父子均需要释放*/
	munmap(mm,sizeof(*mm));
	unlink("mt_test");//删除文件
	return 0;
}
/*
不加锁
可能出现：
父进程：num = :1
父进程：num = :2
子进程：num = :2

子进程：num = :2
父进程：num = :1

加锁之后：num 打印始终是从 1 -- 20
*/