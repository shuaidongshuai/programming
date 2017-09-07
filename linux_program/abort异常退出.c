// 正常退出：
// exit
// _exit
// 异常退出：
// abort
// ctrl + c 

#include <stdio.h>
#include <stdlib.h>

void myFunc1(void)
{
	printf("myFunc1\n");
}

int main()
{
	
	atexit(myFunc1);//这句话打印不出来   原因是：abort是异常退出
	
	printf("main\n");//只有这句话打印出来了
	
	abort();
	
}