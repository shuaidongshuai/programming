#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	long t;
	t=time(0);			/*函数返回当前值*/ 
	printf("%ld\n",t);
}
