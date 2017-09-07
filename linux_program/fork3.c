#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <errno.h>

int test()
{
	pid_t pid = fork();
	if(pid < 0)
		perror("fork");
	else if(0 == pid)
		printf("child1 %d\n",pid);
	else
		printf("parrent1 %d\n",pid);
	return 0;
}

int main()
{
	//test();
	pid_t pid = fork();
	if(pid < 0)
		perror("fork");
	else if(0 == pid)
		printf("child2 %d\n",pid);
	else
		printf("parrent2 %d\n",pid);
	test();
	return 0;
}