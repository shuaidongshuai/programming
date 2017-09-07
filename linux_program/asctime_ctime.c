#include<stdio.h>
#include<time.h>
/* asctime是把时间换成ascll码。
ctime是把时间转换成字符串。*/
int main()
{
	time_t t;
	t=time(NULL);
	struct tm *p;
	p=gmtime(&t);
	printf("%s",asctime(p));		//  asctime  是将tm 格式的时间  转化为字符串
	printf("%s",ctime(&t));			// ctime  是将 日历时间直接转化为  本地时间
}