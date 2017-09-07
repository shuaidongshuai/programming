#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
如果open函数中有O_CREAT这个参数，那么需要给出open的第三个参数。
不然你就只能往这个文件写一次数据，第二次再写你就没权限了
*/
int main()
{
	int fd1;
	int fd2;
	char buf[10] = "dong1";
	pid_t pid = fork();
	if(-1 == pid)
	{
		printf("fork()失败\n");
		return 0;
	}
	if(pid > 0)
	{
		fd1 = open("/home/dong/temp", O_RDWR | O_CREAT, S_IRWXU);、
		fd2 = open("/home/dong/temp2", O_RDWR | O_CREAT, S_IRWXU);
		write(fd1,"hello2",6);
		write(fd2,"dong2",5);
		printf("父进程 fd1 = %d\n", fd1);
		printf("父进程 fd2 = %d\n", fd2);
		wait(NULL);
	}
	else
	{
		fd1 = open("/home/dong/temp", O_RDWR | O_CREAT, S_IRWXU);
		fd2 = open("/home/dong/temp2", O_RDWR | O_CREAT, S_IRWXU);
		write(fd1,"hello2",6);
		write(fd2,"dong2",5);
		printf("子进程 fd1 = %d\n", fd1);
		printf("子进程 fd2 = %d\n", fd2);
	}
    close(fd1);
	close(fd2);

    return 0;
}
/*
父进程 fd1 = 3
父进程 fd2 = 4
子进程 fd1 = 3
子进程 fd2 = 4
可以看出同一个文件返回的fd是一样的
*/