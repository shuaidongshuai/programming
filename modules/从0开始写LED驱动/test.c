#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int fd;
	int val = 1;
	fd = open("/dev/dong_dev", O_RDWR);
	if (fd < 0)
	{
		printf("can't open!\n");
	}
	write(fd, &val, 4);//还没有试先任何功能参数可以随便写，只要进去既可
	return 0;
}