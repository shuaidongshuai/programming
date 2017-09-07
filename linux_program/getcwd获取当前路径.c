#include<unistd.h>
#include<stdio.h>
void main()
{
	char buf[50];
	getcwd(buf,sizeof(buf));
	printf("current working directory is : %s\n",buf);
}