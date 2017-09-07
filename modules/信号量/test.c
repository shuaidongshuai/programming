
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <poll.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


/* fifthdrvtest 
  */
int fd;

void my_signal_fun(int signum)
{
	unsigned char key_val;
	read(fd, &key_val, 1);
	printf("key_val: 0x%x\n", key_val);
	printf("hello dong\n");
}

int main(int argc, char **argv)
{
	unsigned char key_val;
	int ret;
	int Oflags;

	signal(SIGIO, my_signal_fun);//signal函数就是让一个信号与与一个函数对应，每当接收到这个信号就会调用相应的函数。
	
	fd = open("/dev/irq", O_RDWR);
	if (fd < 0)
	{
		printf("can't open!\n");
	}

	fcntl(fd, F_SETOWN, getpid());//把当前进程的ID号告诉驱动程序
	
	//设置异步通知标志,调用fasync
	// 改变fasync标记，最终会调用到驱动的faync > fasync_helper：初始化/释放fasync_struct
	Oflags = fcntl(fd, F_GETFL); 
	fcntl(fd, F_SETFL, Oflags | FASYNC);
	
	while (1)
	{
		sleep(1000);
	}
	
	return 0;
}

