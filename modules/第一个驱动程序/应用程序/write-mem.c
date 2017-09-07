#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd = 0;
	int src = 2013;
	
	/*打开设备文件*/
	fd = open("/dev/memdev0",O_RDWR);
	
	/*写入数据*/
	write(fd, &src, sizeof(int));
	
	/*关闭设备*/
	close(fd);
	
	return 0;	

}
