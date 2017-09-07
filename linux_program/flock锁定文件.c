#include<sys/file.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<stdio.h>
void main()
{
	int fd;
	fd=open("/home/dong/dd/1.txt",O_RDWR);
	if(flock(fd,LOCK_EX)<0)					//  还有些没弄懂的
	{
		printf("flock error\n");
	}
}