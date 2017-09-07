//在进程中为SIGBUS注册处理函数，并向该进程发送SIGBUS信号
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void func(int sign)
{
	if(sign==SIGBUS);
	printf("I have get the SIGBUS\n");
}
int main()
{
	signal(SIGBUS,func);
	pause();
}