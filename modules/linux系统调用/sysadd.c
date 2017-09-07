#include<stdio.h>
#include<linux/unistd.h>
int main()
{
	int result;
	result = syscall(365,10,20);
	printf("10 + 20 = %d\n",result);
	return 0;
}