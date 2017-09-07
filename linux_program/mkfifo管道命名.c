#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#define FIFO "/home/dong/dd/12345"
int main()
{
	int fd,pid;
	char message[100];
	if((pid=mkfifo(FIFO,0777))==-1)				//创建命名g管道   0777 是设置权限  和 umssk 有关  权限=0777-ukask
	{
		perror("create fifo channel failed");
		return 1;
	}
	else
		printf("create success\n");
	if(-1==(fd=open(FIFO,O_RDWR)))				//打开命名管道		fd 是文件的描述符    read  write close都要用到
	{
		perror("cannot open the FIFO");
		return 1;
	}
	if(-1==(write(fd,"hello world",12)))		// 写入消息
	{
		perror("read error");
		return 1;
	}
	else
	{
		printf("write data success!\n");
	}
	if(read(fd,message,100)==-1)
	{
		perror("read error");
		return 1;
	}
	else
		printf("the receive data is %s\n",message);
	close(fd);
	return 0;
	
	
	
	
	
}













