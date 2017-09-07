#include<stdio.h>
#include<sys/time.h>
void func()
{
	int i,j,m=0;
	for(i=0;i<1000;i++)
		for(j=0;j<1000;j++)
			m++;
}
void main()
{
	struct timeval timestar,timeend;
	double timeuse;
	gettimeofday(& timestar,NULL);																		// 第二个参数 一般设为0   我也没有去研究他   
	func();
	gettimeofday(& timeend,NULL);
	timeuse=timeend.tv_sec-timestar.tv_sec+(float)(timeend.tv_usec-timestar.tv_usec)/1000000;			//  第二个时间  减去第一个时间  ==花了 的时间    sec是秒usec是微秒  两者是分开的
	printf("it took %lf second\n",timeuse);
}