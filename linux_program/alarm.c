 // alarm也称为闹钟函数，alarm()用来设置信号SIGALRM在经过参数seconds指定的秒数后传送给目前的进程。
 // 如果参数seconds为0，则之前设置的闹钟会被取消，并将剩下的时间返回。
 // 要注意的是，一个进程只能有一个闹钟时间，如果在调用alarm之前已设置过闹钟时间，则任何以前的闹钟时间都被新值所代替。
#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<signal.h>

void myhandle()
{
	printf("hello world\n");
	alarm(1);//alarm的嵌套，相当于递归了
}

int main()
{
    int i;
   //注册信号处理函数
	if (signal(SIGALRM, myhandle) == SIG_ERR)
	{
		perror("func signal err\n");
		return 0;
	}
    alarm(1);//只发送一次消息
	
	//还有个前提，不能让主进程挂了
	while(1)
	{
	}
	
	return 0;
}