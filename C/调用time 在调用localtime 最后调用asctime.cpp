#include<stdio.h>
#include<time.h>
int main()
{
	time_t t;
	struct tm *p;
	t=time(NULL);
	p=localtime(&t);
	printf("          星期 月 号 时间     年号\n");
	printf("当地时间：%s",asctime(p));
 } 
