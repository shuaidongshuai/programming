#include<stdio.h>
#include<time.h>
int main()
{
	printf("北京时间：\n");
	time_t t;
	struct tm *p;
	t=time(NULL);
	p=localtime(&t);
	printf("%d年%02d月%02d日\t",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday);
	printf("星期%d\n",p->tm_wday);
	printf("%d:%d:%d",p->tm_hour,p->tm_min,p->tm_sec);
}
