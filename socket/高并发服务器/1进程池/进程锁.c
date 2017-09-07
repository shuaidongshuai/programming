
/*
#include <pthread.h>
int pthread_mutexattr_init(pthread_mutexattr_t *attr);
int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared);
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
pshared:
线程锁：PTHREAD_PROCESS_PRIVATE
进程锁：PTHREAD_PROCESS_SHARED
默认情况是线程锁

int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_init()函数是以动态方式创建互斥锁的，参数attr指定了新建互斥锁的属性。如果参数attr为空，则使用默认的互斥锁属性，默认属性为快速互斥锁 。互斥锁的属性在创建锁的时候指定，在LinuxThreads实现中仅有一个锁类型属性，不同的锁类型在试图对一个已经被锁定的互斥锁加锁时表现不同。
pthread_mutexattr_init()函数成功完成之后会返回零，其他任何返回值都表示出现了错误。
函数成功执行后，互斥锁被初始化为未锁住态。


定义函数：void *mmap(void *start, size_t length, int prot, int flags, int fd, off_t offsize);
函数说明：mmap()用来将某个文件内容映射到内存中，对该内存区域的存取即是直接对该文件内容的读写。
start	指向欲对应的内存起始地址，通常设为NULL，代表让系统自动选定地址，对应成功后该地址会返回。
length	代表将文件中多大的部分对应到内存。
prot	 代表映射区域的保护方式，有下列组合：
PROT_EXEC  映射区域可被执行；
PROT_READ  映射区域可被读取；
PROT_WRITE  映射区域可被写入；
MAP_SHARED  对应射区域的写入数据会复制回文件内，而且允许其他映射该文件的进程共享。

在调用mmap()时必须要指定MAP_SHARED 或MAP_PRIVATE。
fd	open()返回的文件描述词，代表欲映射到内存的文件。
offset	文件映射的偏移量，通常设置为0，代表从文件最前方开始对应，offset必须是分页大小的整数倍。
返回值：若映射成功则返回映射区的内存起始地址，否则返回MAP_FAILED(-1)，错误原因存于errno 中。
*/
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
int main(void)
{
	int fd, i;
	struct mt *mm;
	pid_t pid;
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
		for (i=0;i<10;i++){
			pthread_mutex_lock(&mm->mutex);
			mm->num += 1;
			printf("子进程：num = :%d\n",mm->num);
			pthread_mutex_unlock(&mm->mutex);
			sleep(0.2);
		}
	}
	else if (pid > 0) {
		for (i=0; i<10; i++){
			pthread_mutex_lock(&mm->mutex);
			mm->num += 1;
			printf("父进程：num = :%d\n",mm->num);
			pthread_mutex_unlock(&mm->mutex);
			sleep(0.2);
		}
		wait(NULL);
	}
	pthread_mutex_destroy(&mm->mutex);
	pthread_mutexattr_destroy(&mm->mutexattr);
	/* 父子均需要释放*/
	munmap(mm,sizeof(*mm));
	unlink("mt_test");
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