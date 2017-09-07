#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <poll.h>
int main()
{
	int fd;
	unsigned char key_val;
	int ret ;
	struct pollfd fds[1];
	
	fd = open("/dev/irq_dev",O_RDWR);
	if(fd < 0)
	{
		printf("can't open");
		return 0;
	}
	
	fds[0].fd  = fd;
	fds[0].events = POLLIN;		// POLLIN There is data to read.普通或优先级带数据可读

	while(1)
	{
		ret = poll(fds , 1, 5000);//2.是要监听的描述符的数目。3.是一个用毫秒表示的时间，是指定poll在返回前没有接收事件时应该等待的时间
		if(ret == 0)//如果超时  打印 timeout
		{
			printf("timeout = %d\n",ret);
		}
		else//如果中断发生
		{
			read(fd , &key_val , 1);
			printf("key_val = 5\n");
		}
		printf("dong\n");
	}
		
	
	return 0;
} 
/* 
struct pollfd {
	int   fd;         /* file descriptor 
	short events;     /* requested events 
	short revents;    /* returned events 
}; 
*/
