#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int main()
{
	int fd=open("/home/dong/test",O_RDONLY);
	char buf[50];
	read(fd,buf,50);
	printf("%s",buf);
	printf("\n");
	return 1;
}