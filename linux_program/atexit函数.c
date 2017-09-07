#include <stdio.h>
#include <stdlib.h>

void myFunc1(void)
{
	printf("myFunc1\n");
}
void myFunc2(void)
{
	printf("myFunc2\n");
}

int main()
{
	atexit(myFunc1);
	
	printf("main111\n");
	
	atexit(myFunc2);//都会被执行，只是执行的时间是在后面
	
	return 0;
	exit(0);
	
	printf("main222\n");
}
//结果：
// main
// myFunc2
// myFunc1
//先atexit()的函数，后执行