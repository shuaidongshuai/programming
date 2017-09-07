#include<stdio.h>
#include<time.h>
int main()
{
	time_t t;
	t=time(NULL);
	struct tm *p;
	p=localtime(&t);
	printf("%d年%d月%d日星期%d\t%d:%d:%d",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday,p->tm_wday,p->tm_hour,p->tm_min,p->tm_sec);
}
