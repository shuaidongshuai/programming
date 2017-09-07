#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int fd;
	int arg = atoi(argv[1]);
	
    if (argc != 3)
    {
        printf("./dong_led 1 off\n");
        return 0;
    }

    fd = open("/dev/myleds", O_RDWR);
    if (fd < 0)
    {
        printf("error, can't open \n");
        return 0;
    }

    if (!strcmp("on", argv[2]))
    {
        // 亮灯
        ioctl(fd, 0,arg-1);
    }
    if (!strcmp("off", argv[2]))
    {
        // 灭灯
        ioctl(fd, 1,arg-1);
    }

    return 0;
}