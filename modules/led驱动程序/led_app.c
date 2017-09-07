#include<string.h>
#include<stdio.h>
#include<sys/ioctl.h>
//open函数要用到
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include"led.h"

int main(int argc , char *argv[])
{
	int fd;
	int cmd;
	if(argc<2){
		printf("Please cmd\n");
		return 0;
	}
	
	fd = open("/dev/led_dong",O_RDWR);
	
	if(!strcmp(argv[1],"ON"))
	ioctl(fd,LED_ON);
	if(!strcmp(argv[1],"OFF"))
	ioctl(fd,LED_OFF);		
	
	return 0;
}

