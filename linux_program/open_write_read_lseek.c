#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
int main()
{
	char *path="/home/dong/dd/dong.txt";
	int fd,n,i;
	char buf1[50],buf2[]="123456";
	if((fd=open(path,O_RDWR))<0)			//打开文件
	{
		perror("open file failed!");
		return 1;
	}
	else
	{
		printf("open file successful!\n");
	}
	if((n=read(fd,buf1,10))<0)				//读取文件      后面的10是读取字节数
	{
		perror("read failed!");
		return 1;
	}
	else
	{
		printf("output read data:\n");
		printf("%s\n",buf1);
	}
	if((i=lseek(fd,13,SEEK_SET))<0)			//文件的定位
	{
		perror("lseek error:");
		return 1;
	}
	else 
	{
		if(write(fd,buf2,6)<0)				//写入文件
		{
			perror("write error:");
			return 1;
		}
		else{
			printf("write successful!\n");
		}
	}
	close(fd);								//关闭文件
	
	if((fd=open(path,O_RDWR))<0)			//打开文件
	{
		perror("open file failed!");
		return 1;
	}
	else 
	{
		read(fd,buf1,50);
		printf("read the changed  date:\n");
		printf("%s\n",buf1);
	}
	if(close(fd)<0)
	{
		perror("close failed");
		return 1;
	}
	else
		printf("GOOD bye\n");
	
	return 0;
}
