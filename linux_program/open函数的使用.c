#include<stdio.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include<unistd.h>

void main()
{
	int fd;
	fd=open("dong",O_CREAT|O_RDWR,0755);	//   open 打开文件后   会返回  一个文件 描述符
	
	close(fd);								//   要用   unistd.h    这个头文件
}