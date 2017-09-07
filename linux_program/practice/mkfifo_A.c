// 1 .启动A 进程创建一个有名管道，并向里面写入数据
// 2 .启动B 进程从A 创建的管道中读出数据
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>		// 2 3 mkfifo
#include<fcntl.h>			// 2 3 4 open
#include<unistd.h>			//  read write 
#include<string.h>
int main(int argc,char** argv)
{
	if(argc!=2)
	{
		printf("please enter the two paramters\n");
		return 1;
	}
	mkfifo("/home/dong/test",0777);
	int fd;
	fd=open("/home/dong/test",O_WRONLY);
	write(fd,argv[1],50);
	return 1;
}