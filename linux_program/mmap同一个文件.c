#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

/*
void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
start：映射区的开始地址，设置为0时表示由系统决定映射区的起始地址。
length：映射区的长度。//长度单位是 以字节为单位，不足一内存页按一内存页处理
prot：期望的内存保护标志，不能与文件的打开模式冲突。是以下的某个值，可以通过or运算合理地组合在一起
			PROT_EXEC //页内容可以被执行
			PROT_READ //页内容可以被读取
			PROT_WRITE //页可以被写入
			PROT_NONE //页不可访问
flags：指定映射对象的类型，映射选项和映射页是否可以共享。它的值可以是一个或者多个以下位的组合体
			MAP_SHARED //与其它所有映射这个对象的进程共享映射空间。对共享区的写入，相当于输出到文件。直到msync()或者munmap()被调用，文件实际上不会被更新。
fd：有效的文件描述词。一般是由open()函数返回，其值也可以设置为-1，此时需要指定flags参数中的MAP_ANON,表明进行的是匿名映射。
off_toffset：被映射对象内容的起点。
*/
int main()
{
	int fd;
	char *buf = "陈明东";
	char buf2[1024];
	pid_t pid = fork();
	if(-1 == pid)
	{
		printf("fork()失败\n");
		return 0;
	}
	if(pid > 0)
	{
		fd = open("/home/dong/temp", O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
		char *map_mem = mmap(0,1000,PROT_READ,MAP_SHARED,fd,0);
		write(fd,buf,strlen(buf) + 1);
		printf("父进程 fd = %d\t地址：%x内容：%s\n", fd,(void *)map_mem,map_mem);
		sleep(2);
		write(fd,buf,strlen(buf) + 1);
		printf("父进程 fd = %d\t地址：%x内容：%s\n", fd,(void *)map_mem,map_mem);
		wait(0);
	}
	else
	{
		sleep(1);
		fd = open("/home/dong/temp", O_RDWR | O_CREAT, S_IRWXU);
		char *map_mem = mmap(0,1000,PROT_READ,MAP_SHARED,fd,0);
		printf("子进程 fd = %d\t地址：%x内容：%s\n", fd,(void *)map_mem,map_mem);
		if(munmap(map_mem,1000) == 0)//如果解除映射成功则返回0，否则返回－1
		{
			printf("解除映射成功\n");
		}
		//printf("子进程munmap之后\n");		//如果下面这段话不注释，这一句话也不会被打印(下面再次使用map_mem子进程会直接崩溃，都没时间打印就退出了)
		//printf("子进程 fd = %d\t地址：%x内容：%s\n", fd,(void *)map_mem,map_mem);//munmap之后自己就不能再用了，但是别的进程是可以再用的
	}
    close(fd);

    return 0;
}