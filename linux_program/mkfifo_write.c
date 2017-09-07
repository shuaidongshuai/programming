#include<sys/types.h>
#include<sys/stat.h>												 
#include<fcntl.h>													//  123 三个头文件  为了调用  open 

#include<unistd.h>													//  调用  read write sleep 函数	
#include<string.h>													// 调用 strcpy
#include<stdio.h>
int main(int argc,char *argv[])
{
	int fd;
	char buf_w[100];
	strcpy(buf_w,argv[1]);
	fd=open("/home/dong/test",O_WRONLY|O_NONBLOCK);
	
	if(write(fd,buf_w,100)==-1)
	{
		printf("errir write");
		return 0;
	}
	printf("write %s",buf_w);
	return 0;
}