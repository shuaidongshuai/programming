#include<sys/types.h>
#include<sys/stat.h>												// 12  两个头文件  是为了调用  mkfifo  
#include<fcntl.h>													//  123 三个头文件  为了调用  open 

#include<unistd.h>													//  调用  read write sleep 函数
#include<stdio.h>
#include<string.h>													// 调用 memset
int main()
{
		if(mkfifo("/home/dong/test",0777)<0)
		{
			printf("can't creat fifo");
			return 1;
		}
		int fd=open("/home/dong/test",O_RDONLY|O_NONBLOCK);
		if(fd==-1)
		{
			perror("open error\n");												//  一开始老打不开  最后百度 发现    创建的管道没有权限  普通用户打不开
			return 1;
		}
		char buf_r[100];
		while(1)
		{
			memset(buf_r,0,sizeof(buf_r));										//  对内存的初始化
			read(fd,buf_r,100);
			printf("read %s\n",buf_r);
			sleep(1);
		}
		return 0;
}

