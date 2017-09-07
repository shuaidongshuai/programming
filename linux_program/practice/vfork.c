#include<stdio.h>

#include<sys/types.h>
#include<unistd.h>
int main()
{
	pid_t pid;
	int a=0;
	pid=vfork();
	a++;
	printf("a=%d\n",a);
	return 0;
}