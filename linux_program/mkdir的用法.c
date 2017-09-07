#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(int argc,char *argv[])
{
	if(argc<=1)
	{
		printf("dir == mkdir\n");
	}
	else
	{
		mkdir(argv[1],0722);
	}
}