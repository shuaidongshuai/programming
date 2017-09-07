#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
void main(int argc,char *argv[])
{
	if(1==argc)
	{
		printf("a.out == touch\n");
	}
	else{
		creat(argv[1],0777);
	}
}