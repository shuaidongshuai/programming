#include <signal.h>
#include <stdio.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
void sig_init(int signal)
{
	printf("hello signal %d\n",signal);
}

int main()
{
	struct sigaction sigact;
	
	sigact.sa_handler = sig_init;
	
	//sigact.sa_flags = 0;//从输出可以看出，read调用被中断后，没有再重启。\
						这说明我的系统默认就是 对被中断的系统调用不会自动重启。
	sigact.sa_flags |= SA_RESTART;//使用了 SA_RESTART标志后 read调用被中断后 会自动重启 继续等待中断输入。
	if(sigaction(SIGINT,&sigact,NULL) == -1)
	{
		perror("sigacion");
		return 0;
	}
	char c;
	read(0,&c,1);
	printf("read:%c\n",c);
	return 0;
}
/*



*/