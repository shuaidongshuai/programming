#include<stdio.h>
#include<time.h>
int main()
{
	//获取时间种子
	time_t t;
	t=time(NULL);
	printf("s=%ld\n",t);
	// 转化为当地时间
	struct tm *local;
	local=localtime(&t);	// 使用时间 种子  指针
	printf("local hour is %d\n",local->tm_hour);
	// 转化为 格林威治  标准时间
	struct tm *gm;
	gm=gmtime(&t);
	printf("gm hour is %d\n",local->tm_hour);
}